#include "ConcurrentServer.h"
#include <vector>


DWORD WINAPI ResponseServer(LPVOID pPrm) {
	DWORD rc = 0;
	SOCKET servsock;
	WSADATA wsaData;
	SOCKADDR_IN client;  
	int clientsockaddrlen = sizeof(client);
	SOCKADDR_IN serv; 	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(udpport);
	serv.sin_addr.s_addr = ADDR_ANY;

	cout << "ResponseServer работает." << endl;

	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)	throw  SetErrorMsgText("Ошибка при Startup:", WSAGetLastError());
		if ((servsock = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw  SetErrorMsgText("Ошибка при socket:", WSAGetLastError());

		u_long nonblk = 1;
		if (ioctlsocket(servsock, FIONBIO, &(nonblk = 1)) == SOCKET_ERROR)
			throw SetErrorMsgText("Ошибка при ioctlsocket:", WSAGetLastError());

		if (bind(servsock, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw  SetErrorMsgText("Ошибка при bind:", WSAGetLastError());

		while (*((TalkersCommand*)pPrm) != EXIT) {
			char ibuf[50];
			char obuf[100];
			int  libuf = 0;

			memset(ibuf, 0, sizeof(ibuf));
			if ((libuf = recvfrom(servsock, ibuf, sizeof(ibuf) - 1, NULL, (LPSOCKADDR)&client, &clientsockaddrlen)) == SOCKET_ERROR) {
				switch (WSAGetLastError()) {
				case WSAEWOULDBLOCK: {
					Sleep(1000); 
					break;
				}
					default: throw SetErrorMsgText("Ошибка при recv:", WSAGetLastError());
				}
			}
			if (libuf > 0) {
				if (strcmp(ibuf, servercall) == 0) {
					if ((libuf = sendto(servsock, ibuf, strlen(ibuf) + 1, NULL, (LPSOCKADDR)&client, sizeof(client))) == SOCKET_ERROR)
						throw SetErrorMsgText("Ошибка при sendto:", WSAGetLastError());
				}
			}
		}
		if (closesocket(servsock) == SOCKET_ERROR) 
			throw SetErrorMsgText("Ошибка при closesocket:", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Ошибка при WSACleanup:", WSAGetLastError());
	}
	catch (string errorMsgText) {
		cout << errorMsgText << endl;
	}
	cout << "ResponseServer завершил работу." << endl;
	ExitThread(rc);
}
