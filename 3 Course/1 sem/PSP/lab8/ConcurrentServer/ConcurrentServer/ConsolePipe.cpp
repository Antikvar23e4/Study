#include "ConcurrentServer.h"
#include <fstream> 
#include <sstream> 
#include <string>  

DWORD WINAPI ConsolePipe(LPVOID pPrm) {
	setlocale(LC_ALL, "Russian");
	cout << "ConsolePipe работает." << endl;
	HANDLE hPipe;
	try 
	{
		wchar_t name[512];
		swprintf_s(name, sizeof(name) / sizeof(wchar_t), L"\\\\.\\pipe\\DESKTOP-IB5TTO9", pipename.c_str());

		HANDLE hPipe = CreateNamedPipe(name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, NULL, NULL, INFINITE, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) {
			throw SetErrorMsgText("Ошибка при создании ConsolePipe:", GetLastError());
		}

		while (*((TalkersCommand*)pPrm) != EXIT) {
			if (!ConnectNamedPipe(hPipe, NULL)) throw SetErrorMsgText("Ошибка при подключении:", GetLastError());

			char readBuffer[1024], writeBuffer[1024];
			DWORD bytesRead = 0, bytesWrite = 0;
			TalkersCommand SetCommand;
			bool serverCommand;

			while (*((TalkersCommand*)pPrm) != EXIT) {
				if (*((TalkersCommand*)pPrm) == GETCOMMAND) {
					if (!ReadFile(hPipe, readBuffer, sizeof(readBuffer), &bytesRead, NULL)) {
						break;
					}
					if (bytesRead > 0) {
						int n = atoi(readBuffer);
						switch (n) {
							case 1:
								sprintf_s(writeBuffer, "%s", "START");
								SetCommand = TalkersCommand::START;
								break;
							case 2:
								sprintf_s(writeBuffer, "%s", "STOP");
								SetCommand = TalkersCommand::STOP;
								break;
							case 3:
								sprintf_s(writeBuffer, "%s", "EXIT");
								SetCommand = TalkersCommand::EXIT;
								break;
							case 4:
								sprintf_s(writeBuffer, "\nTotal:\t%i\nActive:\t%i\nRejected:\t%i\nTimeOut:\t%i", TotalClients, CurrentClients, RejectedClients, TimeoutConnections);
								SetCommand = TalkersCommand::GETCOMMAND;
								break;
							case 5:
								sprintf_s(writeBuffer, "%s", "WAIT");
								SetCommand = TalkersCommand::WAIT;
								break;
							case 6:
								sprintf_s(writeBuffer, "%s", "SHUTDOWN");
								SetCommand = TalkersCommand::SHUTDOWN;
								break;
							default:
								sprintf_s(writeBuffer, "%s", "error");
								SetCommand = TalkersCommand::GETCOMMAND;
								break;
						}
						*((TalkersCommand*)pPrm) = SetCommand;
						if (!WriteFile(hPipe, writeBuffer, sizeof(writeBuffer), &bytesRead, NULL)) throw SetErrorMsgText("WriteFile error:", GetLastError());
					}
				}
				Sleep(1000);
			}
		}
		DisconnectNamedPipe(hPipe);
		CloseHandle(hPipe);
		cout << "ConsolePipe завершил работу." << endl;

	}
	catch (string ErrorPipeText) {
		cout << ErrorPipeText << endl;
	}
	DWORD rc = 0;
	ExitThread(rc);
}
