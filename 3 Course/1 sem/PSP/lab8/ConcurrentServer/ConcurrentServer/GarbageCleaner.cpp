#include "ConcurrentServer.h"

DWORD WINAPI GarbageCleaner(LPVOID pPrm) {
	try {
		while (&CurrentClients > (volatile LONG*)0  && *((TalkersCommand*)pPrm) != EXIT) {
            EnterCriticalSection(&ListContactCriticalSection);
            if (!Contacts.empty()) {
                for (auto it = Contacts.begin(); it != Contacts.end();) {
                    if (it->sthread == Contact::FINISH || it->sthread == Contact::TIMEOUT || it->sthread == Contact::ABORT) {
                        closesocket(it->s);
                        if (it->hthread != NULL) {
                            if (!CloseHandle(it->hthread)) {
                                cout << SetErrorMsgText("Ошибка при CloseHandle: ", GetLastError()) << endl;
                            }
                        }
                        it = Contacts.erase(it);
                        InterlockedDecrement(&CurrentClients);
                    }
                    else {
                        ++it; 
                    }
                }
            }

            LeaveCriticalSection(&ListContactCriticalSection);
            Sleep(1000);
		}
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}
	DWORD rc = 0;
	ExitThread(rc);
}
