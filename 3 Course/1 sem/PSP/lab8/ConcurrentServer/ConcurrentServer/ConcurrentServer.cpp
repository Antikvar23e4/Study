#include "ConcurrentServer.h"
#include "..\..\ServiceLibrary\ServiceLibrary\DefineTableService.h"
#include <fstream> 
#include <sstream> 
#include <string> 
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm> 

int port = 2000; 
int udpport = 2000;
const char* servercall = "DESKTOP-IB5TTO9";

HANDLE hAcceptServer, hDispatchServer, hGarbageCleaner, hConsolePipe, hResponseServer, hMailslotThread;
HANDLE AcceptEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
HANDLE(*sss)(char*, LPVOID);
HMODULE st;
CRITICAL_SECTION ListContactCriticalSection;
ListContact Contacts;                

const char* dllname = "D:\\University\\1sem\\ПСП\\lab8\\ServiceLibrary\\x64\\Debug\\ServiceLibrary.dll";
wstring pipename = L"RConsole";

volatile LONG CurrentClients;
volatile LONG TotalClients;
volatile LONG RejectedClients;
volatile LONG TimeoutConnections;

bool serverIsStop = false;

struct ScheduleEntry {
    SYSTEMTIME time;
    std::string libraryName;

    // Для сортировки по времени
    bool operator<(const ScheduleEntry& other) const {
        if (time.wYear != other.time.wYear) return time.wYear < other.time.wYear;
        if (time.wMonth != other.time.wMonth) return time.wMonth < other.time.wMonth;
        if (time.wDay != other.time.wDay) return time.wDay < other.time.wDay;
        if (time.wHour != other.time.wHour) return time.wHour < other.time.wHour;
        return time.wMinute < other.time.wMinute;
    }
};

bool ParseScheduleLine(const std::string& line, ScheduleEntry& entry) {
    std::istringstream lineStream(line);
    std::string date, time, libraryName;

    // извлечение данных
    std::getline(lineStream, date, ' ');
    std::getline(lineStream, time, ' ');
    std::getline(lineStream, libraryName);

    int year, month, day;
    if (sscanf_s(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        return false;
    }

    int hour, minute;
    if (sscanf_s(time.c_str(), "%d:%d", &hour, &minute) != 2) {
        return false; 
    }

    // получаем текущую дату
    SYSTEMTIME st;
    GetLocalTime(&st);

    entry.time = st;
    entry.time.wYear = year;
    entry.time.wMonth = month;
    entry.time.wDay = day;
    entry.time.wHour = hour;
    entry.time.wMinute = minute;
    entry.libraryName = libraryName;

    return true;
}

bool IsTimeInPast(const SYSTEMTIME& time) {
    SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);

    if (currentTime.wYear > time.wYear) return true;
    if (currentTime.wMonth > time.wMonth) return true;
    if (currentTime.wDay > time.wDay) return true;
    if (currentTime.wHour > time.wHour) return true;
    if (currentTime.wMinute > time.wMinute) return true;
    return false;
}

void LoadLibraryAtTime(const ScheduleEntry& entry) {
    if (IsTimeInPast(entry.time)) {
        std::cout << "Время для загрузки библиотеки " << entry.libraryName << " уже прошло." << std::endl;
        return;
    }

    SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);

    // ожидания настпуления времени из расписания
    while (currentTime.wHour < entry.time.wHour || (currentTime.wHour == entry.time.wHour && currentTime.wMinute < entry.time.wMinute)) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        GetLocalTime(&currentTime); 
    }

    // загружаем библиотеку
    wchar_t wDllName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, entry.libraryName.c_str(), -1, wDllName, MAX_PATH);
    HMODULE st = LoadLibrary(wDllName);

    if (st) {
        std::cout << "Библиотека " << entry.libraryName << " загружена успешно." << std::endl;
    }
    else {
        std::cerr << "Ошибка загрузки библиотеки " << entry.libraryName << ": " << GetLastError() << std::endl;
    }
}


DWORD WINAPI MailslotServer(LPVOID pPrm) {
    HANDLE hMailslot = CreateMailslot(L"\\\\.\\mailslot\\ServerMailslot", 0, MAILSLOT_WAIT_FOREVER, NULL);

    if (hMailslot == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка создания Mailslot: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Mailslot создан и ожидает сообщений..." << std::endl;

    char buffer[1024];
    DWORD bytesRead;

    while (true) {
        if (ReadFile(hMailslot, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
            buffer[bytesRead] = '\0'; 
            std::cout << "Получено расписание:\n" << buffer << std::endl;

            std::ofstream receivedFile("received_schedule.txt");
            if (receivedFile.is_open()) {
                receivedFile << buffer;
                receivedFile.close();
                std::cout << "Содержимое сохранено в файл received_schedule.txt" << std::endl;
            }
            else {
                std::cerr << "Ошибка: Невозможно сохранить содержимое в файл" << std::endl;
            }

            std::istringstream iss(buffer);
            std::string line;
            std::vector<ScheduleEntry> scheduleEntries;

            while (std::getline(iss, line)) {
                if (line.empty()) continue;

                ScheduleEntry entry;
                if (ParseScheduleLine(line, entry)) {
                    scheduleEntries.push_back(entry);
                }
                else {
                    std::cerr << "Ошибка при разборе строки расписания: " << line << std::endl;
                }
            }
            std::sort(scheduleEntries.begin(), scheduleEntries.end());

            std::cout << "Полученное расписание:" << std::endl;
            for (const auto& entry : scheduleEntries) {
                std::ostringstream dateStream;
                dateStream << (entry.time.wDay < 10 ? "0" : "") << entry.time.wDay << "."
                    << (entry.time.wMonth < 10 ? "0" : "") << entry.time.wMonth << "."
                    << entry.time.wYear;
                std::cout << "Дата: " << dateStream.str()
                    << " Время: " << entry.time.wHour << ":" << (entry.time.wMinute < 10 ? "0" : "") << entry.time.wMinute
                    << " Библиотека: " << entry.libraryName << std::endl;
            }

            for (const auto& entry : scheduleEntries) {
                LoadLibraryAtTime(entry);
            }
        }
        else {
            std::cerr << "Ошибка чтения из Mailslot: " << GetLastError() << std::endl;
        }
    }
    DWORD rc = 0;
    ExitThread(rc);
    CloseHandle(hMailslot);
    return 0;
}


int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc > 1) {
        try {
            port = std::stoi(argv[1]);
        }
        catch (std::exception& e) {
            std::cerr << "Неверный номер порта: " << argv[1] << ". Используется порт по умолчанию - 2000." << std::endl;
            port = 2000;
        }
    }
    if (argc > 2) {
        dllname = argv[2];
    }
    if (argc > 3) {
        pipename = std::wstring(argv[3], argv[3] + strlen(argv[3]));
    }
    if (argc > 4) {
        udpport = std::stoi(argv[4]);
    }
    if (argc > 5) {
        servercall = argv[5];
    }

    std::cout << "Используется порт: " << port << std::endl;

    wchar_t wDllName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, dllname, -1, wDllName, MAX_PATH);
    st = LoadLibrary(wDllName);

    if (!st) {
        std::cout << "Ошибка при LoadLibrary: " << GetLastError() << std::endl;
        return 1;
    }

    SYSTEMTIME stTime;
    GetLocalTime(&stTime);
    char timeBuffer[100];
    sprintf_s(timeBuffer, "%02d:%02d:%02d", stTime.wHour, stTime.wMinute, stTime.wSecond);

    sss = (HANDLE(*)(char*, LPVOID))GetProcAddress(st, "SSS");
    if (!sss) {
        std::cout << "Функция не найдена: " << GetLastError() << std::endl;
        FreeLibrary(st);
        return 1;
    }

    InitializeCriticalSection(&ListContactCriticalSection);

    volatile TalkersCommand cmd = START;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        SetErrorMsgText("Ошибка при WSAStartup", WSAGetLastError());
        return 1;
    }
    CurrentClients = 0;
    TotalClients = 0;
    RejectedClients = 0;
    TimeoutConnections = 0;

    hAcceptServer = CreateThread(NULL, NULL, AcceptServer, (LPVOID)&cmd, NULL, NULL);
    hDispatchServer = CreateThread(NULL, NULL, DispatchServer, (LPVOID)&cmd, NULL, NULL);
    hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner, (LPVOID)&cmd, NULL, NULL);
    hConsolePipe = CreateThread(NULL, NULL, ConsolePipe, (LPVOID)&cmd, NULL, NULL);
    hResponseServer = CreateThread(NULL, NULL, ResponseServer, (LPVOID)&cmd, NULL, NULL);
    hMailslotThread = CreateThread(NULL, NULL, MailslotServer, (LPVOID)&cmd, NULL, NULL);

    SetThreadPriority(hAcceptServer, THREAD_PRIORITY_HIGHEST);
    SetThreadPriority(hGarbageCleaner, THREAD_PRIORITY_LOWEST);

    if (hAcceptServer == NULL || hDispatchServer == NULL || hGarbageCleaner == NULL || hConsolePipe == NULL || hResponseServer == NULL || hMailslotThread == NULL) {
        std::cerr << "Ошибка при создании потокв" << std::endl;
        return 1;
    }

    if (hAcceptServer && hDispatchServer && hGarbageCleaner && hConsolePipe && hResponseServer && hMailslotThread) {
        WaitForSingleObject(hAcceptServer, INFINITE);
        WaitForSingleObject(hDispatchServer, INFINITE);
        WaitForSingleObject(hGarbageCleaner, INFINITE);
        WaitForSingleObject(hConsolePipe, INFINITE);
        WaitForSingleObject(hResponseServer, INFINITE);
        WaitForSingleObject(hMailslotThread, INFINITE);

        CloseHandle(hAcceptServer);
        CloseHandle(hDispatchServer);
        CloseHandle(hGarbageCleaner);
        CloseHandle(hConsolePipe);
        CloseHandle(hResponseServer);
        CloseHandle(hMailslotThread);
    }

    DeleteCriticalSection(&ListContactCriticalSection);
    WSACleanup();
    FreeLibrary(st);

    return 0;
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