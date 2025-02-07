#pragma once
#include "pch.h"
#include "EchoServer.h"

DWORD WINAPI EchoServer(LPVOID pPrm) {
	Contact* client = (Contact*)pPrm;
	char ibuf[100];
    memset(ibuf, 0, sizeof(ibuf));

    char Error[15] = "ErrorInquiry", Start[20] = "Start Message";

    int recv_len;
	try
	{
        QueueUserAPC(ASStartMessage, client->hAcceptServer, (ULONG_PTR)_strdup(client->srvname));

        // доп сообщение из-за неблокир. сокета
        if ((send(client->s, Start, sizeof(Start), NULL)) == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                client->sthread = Contact::FINISH;
            }
            else throw  SetErrorMsgText("TimeServer Send:", WSAGetLastError());
        }


        bool work = false;
        while (!client->TimerOff) {
            client->sthread = Contact::WORK;
            if (client->TimerOff) break;

            if ((recv(client->s, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                    Sleep(100);
                }
                else if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                    client->sthread = Contact::FINISH; 
                    break;
                }
                else throw  SetErrorMsgText("EchoServer Recv:", WSAGetLastError());
            }
            else {
                if (client->TimerOff) break;

                if ((send(client->s, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                    if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                        client->sthread = Contact::FINISH;
                        break;
                    }
                    else throw  SetErrorMsgText("EchoServer Send:", WSAGetLastError());
                }
            }
        }

        QueueUserAPC(ASFinishMessage, client->hAcceptServer, (ULONG_PTR)_strdup(client->srvname));
		client->sthread = Contact::FINISH;
        CancelWaitableTimer(client->htimer);
	}
	catch (string errorMsgText)
	{
        client->sthread = Contact::ABORT;
        CancelWaitableTimer(client->htimer);
		cout << endl << errorMsgText;
	}
	DWORD rc = 0;
	ExitThread(rc);
}

VOID CALLBACK ASStartMessage(ULONG_PTR Parameter) {
    SYSTEMTIME stt;
    GetLocalTime(&stt);
    char* srvname = (char*)Parameter;
    printf("%d.%d.%d %d:%02d %s started\n", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute, srvname);
    free(srvname);
}

VOID CALLBACK ASFinishMessage(ULONG_PTR Parameter) {
    SYSTEMTIME stt;
    GetLocalTime(&stt);
    char* srvname = (char*)Parameter;
    printf("%d.%d.%d %d:%02d %s finished\n", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute, srvname);
    free(srvname);
}



string GetErrorMsgText(int code)
{
    string msgText;
    switch (code)
    {
    case WSAEINTR:          msgText = "WSAEINTR: Function interrupted";
        break;
    case WSAEACCES:         msgText = "WSAEACCES: Permission denied";
        break;
    case WSAEFAULT:         msgText = "WSAEFAULT: Invalid address";
        break;
    case WSAEINVAL:         msgText = "WSAEINVAL: Invalid argument";
        break;
    case WSAEMFILE:         msgText = "WSAEMFILE: Too many open files";
        break;
    case WSAEWOULDBLOCK:    msgText = "WSAEWOULDBLOCK: Resource temporarily unavailable";
        break;
    case WSAEINPROGRESS:    msgText = "WSAEINPROGRESS: Operation in progress";
        break;
    case WSAEALREADY:       msgText = "WSAEALREADY: Operation already in progress";
        break;
    case WSAENOTSOCK:       msgText = "WSAENOTSOCK: Socket operation on nonsocket";
        break;
    case WSAEDESTADDRREQ:   msgText = "WSAEDESTADDRREQ: Destination address required";
        break;
    case WSAEMSGSIZE:       msgText = "WSAEMSGSIZE: Message too long";
        break;
    case WSAEPROTOTYPE:     msgText = "WSAEPROTOTYPE: Protocol wrong type for socket";
        break;
    case WSAENOPROTOOPT:    msgText = "WSAENOPROTOOPT: Protocol not available";
        break;
    case WSAEPROTONOSUPPORT: msgText = "WSAEPROTONOSUPPORT: Protocol not supported";
        break;
    case WSAESOCKTNOSUPPORT: msgText = "WSAESOCKTNOSUPPORT: Socket type not supported";
        break;
    case WSAEOPNOTSUPP:     msgText = "WSAEOPNOTSUPP: Operation not supported";
        break;
    case WSAEPFNOSUPPORT:   msgText = "WSAEPFNOSUPPORT: Protocol family not supported";
        break;
    case WSAEAFNOSUPPORT:   msgText = "WSAEAFNOSUPPORT: Address family not supported by protocol";
        break;
    case WSAEADDRINUSE:     msgText = "WSAEADDRINUSE: Address already in use";
        break;
    case WSAEADDRNOTAVAIL:  msgText = "WSAEADDRNOTAVAIL: Cannot assign requested address";
        break;
    case WSAENETDOWN:       msgText = "WSAENETDOWN: Network is down";
        break;
    case WSAENETUNREACH:    msgText = "WSAENETUNREACH: Network is unreachable";
        break;
    case WSAENETRESET:      msgText = "WSAENETRESET: Network dropped connection";
        break;
    case WSAECONNABORTED:   msgText = "WSAECONNABORTED: Software caused connection abort";
        break;
    case WSAECONNRESET:     msgText = "WSAECONNRESET: Connection reset by peer";
        break;
    case WSAENOBUFS:        msgText = "WSAENOBUFS: No buffer space available";
        break;
    case WSAEISCONN:        msgText = "WSAEISCONN: Socket is already connected";
        break;
    case WSAENOTCONN:       msgText = "WSAENOTCONN: Socket is not connected";
        break;
    case WSAESHUTDOWN:      msgText = "WSAESHUTDOWN: Cannot send after socket shutdown";
        break;
    case WSAETIMEDOUT:      msgText = "WSAETIMEDOUT: Connection timed out";
        break;
    case WSAECONNREFUSED:   msgText = "WSAECONNREFUSED: Connection refused";
        break;
    case WSAEHOSTDOWN:      msgText = "WSAEHOSTDOWN: Host is down";
        break;
    case WSAEHOSTUNREACH:   msgText = "WSAEHOSTUNREACH: No route to host";
        break;
    case WSAEPROCLIM:       msgText = "WSAEPROCLIM: Too many processes";
        break;
    case WSASYSNOTREADY:    msgText = "WSASYSNOTREADY: Network subsystem is unavailable";
        break;
    case WSAVERNOTSUPPORTED: msgText = "WSAVERNOTSUPPORTED: Version not supported";
        break;
    case WSANOTINITIALISED: msgText = "WSANOTINITIALISED: Winsock not initialized";
        break;
    case WSAEDISCON:        msgText = "WSAEDISCON: Graceful disconnect in progress";
        break;
    case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND: Class not found";
        break;
    case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND: Host not found";
        break;
    case WSATRY_AGAIN:      msgText = "WSATRY_AGAIN: Try again later";
        break;
    case WSANO_RECOVERY:    msgText = "WSANO_RECOVERY: Non-recoverable error";
        break;
    case WSANO_DATA:        msgText = "WSANO_DATA: No data of requested type";
        break;
    case WSA_INVALID_HANDLE: msgText = "WSA_INVALID_HANDLE: Invalid event handle";
        break;
    case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER: Invalid parameter";
        break;
    case WSA_IO_INCOMPLETE: msgText = "WSA_IO_INCOMPLETE: Overlapped I/O operation not completed";
        break;
    case WSA_IO_PENDING:    msgText = "WSA_IO_PENDING: Operation will complete later";
        break;
    case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY: Not enough memory";
        break;
    case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED: Operation aborted";
        break;
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE: System call failure";
        break;
    default:                msgText = "***ERROR***";
        break;
    };
    return msgText;
};


string SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};
