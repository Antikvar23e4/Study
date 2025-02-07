#include "iostream"
#include "Winsock2.h"

using namespace std;

string GetErrorMsgText(int code);
string SetMailError(string msgText, int code);


string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "The function was interrupted"; break;
	case WSAEACCES: msgText = "Permission denied"; break;
	case WSAEFAULT: msgText = "Bad address"; break;
	case WSAEINVAL: msgText = "Invalid argument"; break;
	case WSAEMFILE: msgText = "Too many open files"; break;
	case WSAEWOULDBLOCK: msgText = "Resource temporarily unavailable"; break;
	case WSAEINPROGRESS: msgText = "Operation now in progress"; break;
	case WSAEALREADY: msgText = "Operation already in progress"; break;
	case WSAENOTSOCK: msgText = "Socket operation on non-socket"; break;
	case WSAEDESTADDRREQ: msgText = "Destination address required"; break;
	case WSAEMSGSIZE: msgText = "Message too long"; break;
	case WSAEPROTOTYPE: msgText = "Protocol wrong type for socket"; break;
	case WSAENOPROTOOPT: msgText = "Bad protocol option"; break;
	case WSAEPROTONOSUPPORT: msgText = "Protocol not supported"; break;
	case WSAESOCKTNOSUPPORT: msgText = "Socket type not supported"; break;
	case WSAEOPNOTSUPP: msgText = "Operation not supported"; break;
	case WSAEPFNOSUPPORT: msgText = "Protocol family not supported"; break;
	case WSAEAFNOSUPPORT: msgText = "Address family not supported by protocol"; break;
	case WSAEADDRINUSE: msgText = "Address already in use"; break;
	case WSAEADDRNOTAVAIL: msgText = "Cannot assign requested address"; break;
	case WSAENETDOWN: msgText = "Network is down"; break;
	case WSAENETUNREACH: msgText = "Network is unreachable"; break;
	case WSAENETRESET: msgText = "Network dropped connection"; break;
	case WSAECONNABORTED: msgText = "Software caused connection abort"; break;
	case WSAECONNRESET: msgText = "Connection reset by peer"; break;
	case WSAENOBUFS: msgText = "No buffer space available"; break;
	case WSAEISCONN: msgText = "Socket is already connected"; break;
	case WSAENOTCONN: msgText = "Socket is not connected"; break;
	case WSAESHUTDOWN: msgText = "Cannot send after socket shutdown"; break;
	case WSAETIMEDOUT: msgText = "Connection timed out"; break;
	case WSAECONNREFUSED: msgText = "Connection refused"; break;
	case WSAEHOSTDOWN: msgText = "Host is down"; break;
	case WSAEHOSTUNREACH: msgText = "No route to host"; break;
	case WSAEPROCLIM: msgText = "Too many processes"; break;
	case WSASYSNOTREADY: msgText = "Network subsystem is unavailable"; break;
	case WSAVERNOTSUPPORTED: msgText = "Winsock version not supported"; break;
	case WSANOTINITIALISED: msgText = "WS2_32.dll not initialized"; break;
	case WSAEDISCON: msgText = "Graceful shutdown in progress"; break;
	case WSATYPE_NOT_FOUND: msgText = "Class type not found"; break;
	case WSAHOST_NOT_FOUND: msgText = "Host not found"; break;
	case WSATRY_AGAIN: msgText = "Non-authoritative host not found"; break;
	case WSANO_RECOVERY: msgText = "This is a non-recoverable error"; break;
	case WSANO_DATA: msgText = "No data record of requested type"; break;
	case WSASYSCALLFAILURE: msgText = "System call failure"; break;
	case ERROR_INVALID_PARAMETER: msgText = "The value of parameter ERROR_INVALID_PARAMETER"; break;
	case ERROR_NO_DATA: msgText = "The pipe is being closed"; break;
	case ERROR_PIPE_CONNECTED: msgText = "A process on the other end of the pipe"; break;
	case ERROR_PIPE_LISTENING: msgText = "Waiting for a process to open the other end of the pipe"; break;
	case ERROR_CALL_NOT_IMPLEMENTED: msgText = "This function is not supported on this system"; break;
	default: msgText = "**ERROR**"; break;
	}

	return msgText;
}

string SetMailError(string msgText, int code)
{
	return msgText + GetErrorMsgText(code) + "\n\n";
}

void main()
{
	setlocale(LC_ALL, "RU");

	HANDLE mailslot;
	HANDLE hClientSlot;
	char buffer[500];         
	DWORD bytesRead, bytesWritten;
	clock_t start, end;

	try
	{
		// MAILSLOT_WAIT_FOREVER
		if ((mailslot = CreateMailslot(L"\\\\.\\mailslot\\Box", 500, 180000, NULL)) == INVALID_HANDLE_VALUE)
		{
			throw SetMailError("Ошибка в CreateMailslot: ", GetLastError());
		}

		while (true) {
			if (!ReadFile(mailslot, buffer, sizeof(buffer), &bytesRead, NULL))
			{
				if (GetLastError() == ERROR_SEM_TIMEOUT) {
					cout << "Время ожидания вышло." << endl;
				}
				else {
					throw SetMailError("Ошибка в ReadFile: ", GetLastError());
				}
			}
			else cout << buffer << endl;
		}



		if (!CloseHandle(mailslot))
		{
			throw SetMailError("Ошибка при закрытии дескриптора: ", GetLastError());
		}
	}
	catch (string e)
	{
		cout << e << endl;
	}
}