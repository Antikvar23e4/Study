#include <tchar.h>
#include "iostream"
#include "Windows.h"                
#include "ctime"
#include <string>
#include <fstream>
#include <sstream>
using std::string;
using namespace std;

string SetPipeError(string msgText, int code);
string GetPipeError(int code);


int main(int argc, _TCHAR* argv[]) {
	setlocale(LC_ALL, "Russian");

	char ReadBuf[1024] = "", WriteBuf[1024] = "";
	DWORD nBytesRead, nBytesWrite;

	int command = 0;

	try
	{
        cout << "\n -------------------Команды---------------- \n";
        cout << "1 - Start\tразрешить подключение клиентов к серверу\n";
        cout << "2 - Stop\tзапретить подключение клиентов к серверу\n";
        cout << "3 - Exit\tзавершить работу сервера\n";
        cout << "4 - Statistics\tвывод статистики\n";
        cout << "5 - Wait\tприостановить подключение клиентов, пока не обслужится последний клиент, подключенный к серверу\n";
        cout << "6 - Shutdown\tравносильна последовательности команд: wait, exit\n";
        cout << "7 - Отправить расписание через Mailslot\n";
        cout << "0 - Выход из консоли\n";
        cout << "\n ----------------------------------------- \n";

        HANDLE hNamedPipe;
        wstring  pipename;
        wchar_t name[512];
        cout << "Введите имя сервера: ";
        wcin >> pipename;

        swprintf_s(name, sizeof(name) / sizeof(wchar_t), L"\\\\.\\pipe\\%s", pipename.c_str());

        wcout << L"Подключение к каналу: " << name << endl;

            
        if ((hNamedPipe = CreateFile(name,
            GENERIC_READ | GENERIC_WRITE,
            NULL,
            NULL,
            OPEN_EXISTING,
            NULL,
            NULL)) == INVALID_HANDLE_VALUE)
        {
            throw SetPipeError("Ошибка при CreateFile:", GetLastError());
        }

        while (true) {
            cout << "Введите команду:" << endl;
            scanf_s("%d", &command);

            if (command > 0 && command <= 7) {
                if (command == 7) { 
                    string scheduleFileName = "scheduleForServer.txt"; // имя файла с расписанием
                    ifstream file(scheduleFileName);

                    if (!file.is_open()) {
                        cerr << "Ошибка: Невозможно открыть файл " << scheduleFileName << endl;
                        continue;
                    }

                    //  содержимое файла
                    stringstream buffer;
                    buffer << file.rdbuf();
                    string fileContent = buffer.str();
                    file.close();

                    // отправляем  через Mailslot
                    HANDLE hMailslot = CreateFile(L"\\\\.\\mailslot\\ServerMailslot",
                        GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

                    if (hMailslot == INVALID_HANDLE_VALUE) {
                        cerr << "Ошибка: Невозможно подключиться к Mailslot" << endl;
                        continue;
                    }

                    DWORD bytesWritten;
                    if (!WriteFile(hMailslot, fileContent.c_str(), fileContent.size() + 1, &bytesWritten, NULL)) {
                        cerr << "Ошибка записи в Mailslot" << endl;
                    }
                    else {
                        cout << "Файл " << scheduleFileName << " успешно отправлен через Mailslot" << endl;
                    }

                    CloseHandle(hMailslot);
                }
                else {
                    sprintf_s(WriteBuf, "%d", command);

                    if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL))
                        throw "Ошибка при WriteFile ";
                    if (!ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
                        throw "Ошибка при ReadFile";

                    if (command == 3) {
                        cout << "Сервер завершает работу. Консоль недоступна." << endl;
                        break;
                    }
                    if (command == 6) {
                        cout << "Сервер завершает работу. Консоль недоступна." << endl;
                        break;
                    }
                    if (command == 4) {
                        sprintf_s(WriteBuf, "%d", command);

                        if (!WriteFile(hNamedPipe, WriteBuf, strlen(WriteBuf) + 1, &nBytesWrite, NULL))
                            throw "Ошибка при WriteFile";
                        if (!ReadFile(hNamedPipe, ReadBuf, sizeof(ReadBuf), &nBytesRead, NULL))
                            throw "Ошибка при ReadFile";

                        cout << "Статистика: " << ReadBuf << endl;
                    }
                }
            }
            else if (command == 0) {
                break;
            }
        }

        if (!CloseHandle(hNamedPipe))
            throw SetPipeError("Ошибка при CloseHandle: ", GetLastError());

        cout << "Программа завершена." << endl;
    }
    catch (string ErrorPipeText) {
        cout << endl << ErrorPipeText;
    }
    return 0;
}

string SetPipeError(string msgText, int code)
{
    return msgText + GetPipeError(code);
}

string GetPipeError(int code)
{
    string msgText;
    switch (code)
    {
    case WSAEINTR:
        msgText = "Function interrupted";
        break;
    case WSAEACCES:
        msgText = "Permission denied";
        break;
    case WSAEFAULT:
        msgText = "Wrong address";
        break;
    case WSAEINVAL:
        msgText = "Wrong args";
        break;
    case WSAEMFILE:
        msgText = "Too many files have opened";
        break;
    case WSAEWOULDBLOCK:
        msgText = "Resource temporarily unavailable";
        break;
    case WSAEINPROGRESS:
        msgText = "Operation in progress";
        break;
    case WSAEALREADY:
        msgText = "Operation already in progress";
        break;
    case WSAENOTSOCK:
        msgText = "Wrong socket";
        break;
    case WSAEDESTADDRREQ:
        msgText = "Required adress location";
        break;
    case WSAEMSGSIZE:
        msgText = "Message is too long ";
        break;
    case WSAEPROTOTYPE:
        msgText = "Wrong protocol type to socket";
        break;
    case WSAENOPROTOOPT:
        msgText = "Error in protocol option";
        break;
    case WSAEPROTONOSUPPORT:
        msgText = "Protocol is not supported";
        break;
    case WSAESOCKTNOSUPPORT:
        msgText = "Socket type is not supported";
        break;
    case WSAEOPNOTSUPP:
        msgText = "Operation is not supported";
        break;
    case WSAEPFNOSUPPORT:
        msgText = "Protocol type is not supported";
        break;
    case WSAEAFNOSUPPORT:
        msgText = "Addresses type is not supported by protocol";
        break;
    case WSAEADDRINUSE:
        msgText = "Address is already used";
        break;
    case WSAEADDRNOTAVAIL:
        msgText = "Requested address cannot be used";
        break;
    case WSAENETDOWN:
        msgText = "Network disconnected";
        break;
    case WSAENETUNREACH:
        msgText = "Network is unttainable";
        break;
    case WSAENETRESET:
        msgText = "Network dropped the connection";
        break;
    case WSAECONNABORTED:
        msgText = "Connection aborted";
        break;
    case WSAECONNRESET:
        msgText = "Connection restored";
        break;
    case WSAENOBUFS:
        msgText = "Not enough memory for buffers";
        break;
    case WSAEISCONN:
        msgText = "Socket has already connected";
        break;
    case WSAENOTCONN:
        msgText = "Socket has not connected";
        break;
    case WSAESHUTDOWN:
        msgText = "Send cannot be performed: socket was shutdowned";
        break;
    case WSAETIMEDOUT:
        msgText = "Alloted time interval has ended";
        break;
    case WSAECONNREFUSED:
        msgText = "Connection was rejected";
        break;
    case WSAEHOSTDOWN:
        msgText = "Host was shotdowned";
        break;
    case WSAEHOSTUNREACH:
        msgText = "Has not way for host";
        break;
    case WSAEPROCLIM:
        msgText = "Too many processes";
        break;
    case WSASYSNOTREADY:
        msgText = "Network is unavailable";
        break;
    case WSAVERNOTSUPPORTED:
        msgText = "Version is not supported";
        break;
    case WSANOTINITIALISED:
        msgText = "WS2_32.dll is not initialised";
        break;
    case WSAEDISCON:
        msgText = "Connection in progress";
        break;
    case WSATYPE_NOT_FOUND:
        msgText = "Type is not found";
        break;
    case WSAHOST_NOT_FOUND:
        msgText = "Host is not found";
        break;
    case WSATRY_AGAIN:
        msgText = "Try again";
        break;
    case WSANO_RECOVERY:
        msgText = "Unknown error";
        break;
    case WSANO_DATA:
        msgText = "Has not data type";
        break;
    case WSAEINVALIDPROCTABLE:
        msgText = "Invalid provider";
        break;
    case WSAEINVALIDPROVIDER:
        msgText = "Error in provider version";
        break;
    case WSAEPROVIDERFAILEDINIT:
        msgText = "Failed provider initialization";
        break;
    case WSASYSCALLFAILURE:
        msgText = "Abnormal termination of a system call";
        break;
    default:
        msgText = "Unknown error";
        break;
    }
    return msgText;
}