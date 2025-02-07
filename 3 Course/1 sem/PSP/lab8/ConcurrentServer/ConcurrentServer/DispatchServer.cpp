#include "ConcurrentServer.h"
#include <fstream> 
#include <sstream> 
#include <string>  

DWORD WINAPI DispatchServer(LPVOID pPrm) {
	cout << "DispathServer работает." << endl;
	char buffer[1024], Error[15] = "Ошибка";
	int bytesReceived, bytesSent;

	try {
		Contact* client = NULL;
		while (*((TalkersCommand*)pPrm) != EXIT) {
			if (WaitForSingleObject(AcceptEvent, 100) == WAIT_OBJECT_0) {
				EnterCriticalSection(&ListContactCriticalSection);
				for (auto it = Contacts.begin(); it != Contacts.end(); it++) {
					if (it->type == Contact::ACCEPT)
					{
						client = &(*it);
						bool flag = false;
						while (flag == false) {
							if ((bytesReceived = recv(client->s, buffer, sizeof(buffer) - 1, 0)) == SOCKET_ERROR) {
								if (WSAGetLastError() == WSAEWOULDBLOCK) {
									Sleep(100);
								}
								else if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET || WSAGetLastError() == WSAENOTSOCK) {
									closesocket(client->s);
									client->s = INVALID_SOCKET;
									client->sthread == Contact::FINISH;
									break;
								}
								else {
									cerr << SetErrorMsgText("Ошибка при recv: ", GetLastError()) << endl;
									break;
								}
							}
							else flag = true;
						}
						if (client && client->s == INVALID_SOCKET) {
							client->sthread == Contact::FINISH;
							break; 
						}
						if (flag)
						{	
							buffer[bytesReceived] = '\0';
							cout << "\tСообщение клиента: " << buffer << endl;
							if (strcmp(buffer, "LOADSCHEDULE") == 0) {
								std::ifstream scheduleFile("schedule.txt");
								if (!scheduleFile.is_open()) {
									cerr << "Error: Unable to open schedule file" << endl;
									break;
								}

								std::string schedule((std::istreambuf_iterator<char>(scheduleFile)), std::istreambuf_iterator<char>());
								scheduleFile.close();

								if (send(client->s, schedule.c_str(), schedule.length(), 0) == SOCKET_ERROR) {
									cerr << "Ошибка при отправке расписания: " << WSAGetLastError() << endl;
								}
								else {
									cout << "Расписание отпрвлено" << endl;
								}
							}



							client->type = Contact::CONTACT;
							client->htimer = CreateWaitableTimer(NULL, false, NULL);
							if (client->htimer == NULL) {
								cerr << SetErrorMsgText("Ошибка при CreateWaitableTimer", GetLastError()) << endl;
							}
							_int64 time = -100000000;
							if (!SetWaitableTimer(client->htimer, (LARGE_INTEGER*)&time, 0, ASWTimer, client, false)) {
								cerr << SetErrorMsgText("Ошибка при SetWaitableTimer", GetLastError()) << endl;
								CloseHandle(client->htimer);
								client->htimer = NULL;
							}
							strcpy_s(client->srvname, buffer);

							client->hthread = sss(buffer, client);
							if (!client->hthread) {
								flag = false;
							}
						}
						if (!flag) {
							InterlockedIncrement(&RejectedClients);
							if ((bytesSent = send(client->s, Error, sizeof(Error), NULL)) == SOCKET_ERROR)
								throw SetErrorMsgText("Ошибка при send: ", WSAGetLastError());
							if (client->htimer != NULL) {
								if (!CancelWaitableTimer(client->htimer)) {
									cerr << SetErrorMsgText("Ошибка при CancelWaitableTimer", GetLastError()) << endl;
									CloseHandle(client->htimer);
									client->htimer = NULL;
								}
							}
							client->sthread = Contact::ABORT;
							closesocket(client->s);
						}
					}
				}
				LeaveCriticalSection(&ListContactCriticalSection);
			}
			SleepEx(0, TRUE);
		}
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}
	DWORD rc = 0;
	ExitThread(rc);
}

void CALLBACK ASWTimer(LPVOID Lprm, DWORD, DWORD) {
	char obuf[50] = "Таймер закрыт";
	Contact* client = (Contact*)Lprm;
	char* name = client->srvname;
	EnterCriticalSection(&ListContactCriticalSection);

	if ((send(client->s, obuf, sizeof(obuf), NULL)) == SOCKET_ERROR) throw  SetErrorMsgText("Ошибка при send:", WSAGetLastError());

	client->TimerOff = true;
	client->sthread = Contact::TIMEOUT;
	TerminateThread(client->hthread, 0);
	LeaveCriticalSection(&ListContactCriticalSection);
	TimeoutConnections += 1;
	SYSTEMTIME stt;
	GetLocalTime(&stt);
	printf("%d.%d.%d %d:%02d %s timeout\n", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute, name);
}