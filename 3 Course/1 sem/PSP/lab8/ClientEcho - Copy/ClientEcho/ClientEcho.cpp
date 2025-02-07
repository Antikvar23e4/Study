#include "Winsock2.h"                
#pragma comment(lib, "WS2_32.lib") 
#include <ws2tcpip.h>

#include <iostream>
#include <string>

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);



bool  GetServerByName(char* name, char* call, struct sockaddr* from, int* flen) {
    SOCKET sS;
    sS = socket(AF_INET, SOCK_DGRAM, NULL);

    if (sS == INVALID_SOCKET) {
        cout << "Socket creation failed: " << WSAGetLastError() << endl;
    }

    struct addrinfo hints, * res; // hostent
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(name, nullptr, &hints, &res) != 0) { // gethostbyname               
        throw SetErrorMsgText("getaddrinfo:", WSAGetLastError());
    }

    char ip_addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &((struct sockaddr_in*)res->ai_addr)->sin_addr, ip_addr, INET_ADDRSTRLEN);

    cout << "\nServer IP: " << ip_addr << endl;

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    if (inet_pton(AF_INET, ip_addr, &server_addr.sin_addr) <= 0) {
        cerr << "inet_pton failed for address: " << ip_addr << " with error: " << WSAGetLastError() << endl;
        closesocket(sS);
        return false;
    }

    int sent_len;
    int recv_len;
    char buffer[50];

    if ((sent_len = sendto(sS, call, strlen(call), 0, (sockaddr*)&server_addr, sizeof(server_addr))) == SOCKET_ERROR) {
        closesocket(sS);
        cout << SetErrorMsgText("sendto: ", WSAGetLastError()) << endl;
        return false;
    }

    int timeout = 20000;
    if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) {
        closesocket(sS);
        cout << SetErrorMsgText("setsockopt (SO_RCVTIMEO): ", WSAGetLastError()) << endl;
        return false;
    }

    memset(buffer, 0, sizeof(buffer));
    if ((recv_len = recvfrom(sS, buffer, sizeof(buffer) - 1, 0, from, flen)) == SOCKET_ERROR) {

        if (WSAGetLastError() == WSAETIMEDOUT) {
            cout << "Connection timed out." << endl;
            closesocket(sS);
            return false;
        }
        else {
            closesocket(sS);
            cout << SetErrorMsgText("recvfrom: ", WSAGetLastError()) << endl;
            return false;
        }
    }
    if (strcmp(buffer, call) == 0) {
        closesocket(sS);
        return true;
    }
    else {
        closesocket(sS);
        return false;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    SOCKET  sS;
    WSADATA wsaData;
    char ip[INET_ADDRSTRLEN];


    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("startup:", WSAGetLastError());

        sockaddr_in server_addr;  // Структура для хранения параметров сервера
        int addr_len = sizeof(server_addr);  // Размер структуры server_addr
        char name[] = "DESKTOP-IB5TTO9"; //
        short port = 2000;
        char call[] = "";
        if (GetServerByName(name, name, (sockaddr*)&server_addr, &addr_len))
        {
            inet_ntop(AF_INET, &(server_addr.sin_addr), ip, INET_ADDRSTRLEN);

            cout << "Connected server: " << endl;
            cout << "IP: " << ip << endl;
            cout << "Port: " << htons(server_addr.sin_port) << endl;
        }
        else {
            cout << "Error connected server\n";
        }
        if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());

        SOCKADDR_IN serv;
        serv.sin_family = AF_INET;
        serv.sin_port = server_addr.sin_port;

        if (inet_pton(AF_INET, ip, &serv.sin_addr) <= 0)
            throw SetErrorMsgText("inet_pton:", WSAGetLastError());

        if ((connect(sS, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw SetErrorMsgText("connect:", WSAGetLastError());
        cout << "Connected" << endl;

        int fbuf = 0;
        char firbuf[100];
        snprintf(firbuf, sizeof(firbuf), "echo");
        if ((fbuf = send(sS, firbuf, strlen(firbuf) + 1, NULL)) == SOCKET_ERROR)
            throw  SetErrorMsgText("send:", WSAGetLastError());

        cout << "Client sent to the server: " << firbuf << endl;

        int lobuf = 0, libuf = 0;
        char obuf[100] = "Hello from Client!";
        char ibuf[100];

        Sleep(100);

        for (int i = 0; i < 100000; i++) {

            if ((lobuf = send(sS, obuf, sizeof(obuf), NULL)) == SOCKET_ERROR)
                throw  SetErrorMsgText("send:", WSAGetLastError());

            cout << "Client sent to the server: " << obuf << endl;


            if ((libuf = recv(sS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
                throw  SetErrorMsgText("recv:", WSAGetLastError());

            cout << "Client received from the server: " << ibuf << endl;

            Sleep(500);
        }

        if (closesocket(sS) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
    return 0;
}

string GetErrorMsgText(int code)
{
    string msgText;
    switch (code)
    {
    case WSAEINTR:          msgText = "WSAEINTR: Работа функции прервана";
        break;
    case WSAEACCES:         msgText = "WSAEACCES: Разрешение отвергнуто";
        break;
    case WSAEFAULT:         msgText = "WSAEFAULT: Ошибочный адрес";
        break;
    case WSAEINVAL:         msgText = "WSAEINVAL: Ошибка в аргументе";
        break;
    case WSAEMFILE:         msgText = "WSAEMFILE: Слишком много файлов открыто";
        break;
    case WSAEWOULDBLOCK:    msgText = "WSAEWOULDBLOCK: Ресурс временно недоступен";
        break;
    case WSAEINPROGRESS:    msgText = "WSAEINPROGRESS: Операция в процессе развития";
        break;
    case WSAEALREADY:       msgText = "WSAEALREADY: Операция уже выполняется";
        break;
    case WSAENOTSOCK:       msgText = "WSAENOTSOCK: Сокет задан неправильно";
        break;
    case WSAEDESTADDRREQ:   msgText = "WSAEDESTADDRREQ: Требуется адрес расположения";
        break;
    case WSAEMSGSIZE:       msgText = "WSAEMSGSIZE: Сообщение слишком длинное";
        break;
    case WSAEPROTOTYPE:     msgText = "WSAEPROTOTYPE: Неправильный тип протокола для сокета";
        break;
    case WSAENOPROTOOPT:    msgText = "WSAENOPROTOOPT: Ошибка в опции протокола";
        break;
    case WSAEPROTONOSUPPORT: msgText = "WSAEPROTONOSUPPORT: Протокол не поддерживается";
        break;
    case WSAESOCKTNOSUPPORT: msgText = "WSAESOCKTNOSUPPORT: Тип сокета не поддерживается";
        break;
    case WSAEOPNOTSUPP:     msgText = "WSAEOPNOTSUPP: Операция не поддерживается";
        break;
    case WSAEPFNOSUPPORT:   msgText = "WSAEPFNOSUPPORT: Тип протоколов не поддерживается";
        break;
    case WSAEAFNOSUPPORT:   msgText = "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом";
        break;
    case WSAEADDRINUSE:     msgText = "WSAEADDRINUSE: Адрес уже используется";
        break;
    case WSAEADDRNOTAVAIL:  msgText = "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован";
        break;
    case WSAENETDOWN:       msgText = "WSAENETDOWN: Сеть отключена";
        break;
    case WSAENETUNREACH:    msgText = "WSAENETUNREACH: Сеть не достижима";
        break;
    case WSAENETRESET:      msgText = "WSAENETRESET: Сеть разорвала соединение";
        break;
    case WSAECONNABORTED:   msgText = "WSAECONNABORTED: Программный отказ связи";
        break;
    case WSAECONNRESET:     msgText = "WSAECONNRESET: Связь восстановлена";
        break;
    case WSAENOBUFS:        msgText = "WSAENOBUFS: Не хватает памяти для буферов";
        break;
    case WSAEISCONN:        msgText = "WSAEISCONN: Сокет уже подключен";
        break;
    case WSAENOTCONN:       msgText = "WSAENOTCONN: Сокет не подключен";
        break;
    case WSAESHUTDOWN:      msgText = "WSAESHUTDOWN: Нельзя выполнить send: сокет завершил работу";
        break;
    case WSAETIMEDOUT:      msgText = "WSAETIMEDOUT: Закончился отведенный интервал времени";
        break;
    case WSAECONNREFUSED:   msgText = "WSAECONNREFUSED: Соединение отклонено";
        break;
    case WSAEHOSTDOWN:      msgText = "WSAEHOSTDOWN: Хост в неработоспособном состоянии";
        break;
    case WSAEHOSTUNREACH:   msgText = "WSAEHOSTUNREACH: Нет маршрута для хоста";
        break;
    case WSAEPROCLIM:       msgText = "WSAEPROCLIM: Слишком много процессов";
        break;
    case WSASYSNOTREADY:    msgText = "WSASYSNOTREADY: Сеть не доступна";
        break;
    case WSAVERNOTSUPPORTED: msgText = "WSAVERNOTSUPPORTED: Данная версия недоступна";
        break;
    case WSANOTINITIALISED: msgText = "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL";
        break;
    case WSAEDISCON:        msgText = "WSAEDISCON: Выполняется отключение";
        break;
    case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND: Класс не найден";
        break;
    case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND: Хост не найден";
        break;
    case WSATRY_AGAIN:      msgText = "WSATRY_AGAIN: Неавторизированный хост не найден";
        break;
    case WSANO_RECOVERY:    msgText = "WSANO_RECOVERY: Неопределенная ошибка";
        break;
    case WSANO_DATA:        msgText = "WSANO_DATA: Нет записи запрошенного типа";
        break;
    case WSA_INVALID_HANDLE: msgText = "WSA_INVALID_HANDLE: Указанный дескриптор события с ошибкой";
        break;
    case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой";
        break;
    case WSA_IO_INCOMPLETE: msgText = "WSA_IO_INCOMPLETE: Объект ввода-вывода не в сигнальном состоянии";
        break;
    case WSA_IO_PENDING:    msgText = "WSA_IO_PENDING: Операция завершится позже";
        break;
    case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти";
        break;
    case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED: Операция отвергнута";
        break;
    case WSASYSCALLFAILURE: msgText = "WSASYSCALLFAILURE: Аварийное завершение системного вызова";
        break;
    default:                msgText = "***ERROR***";        break;
    };
    return msgText;
};

string SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};