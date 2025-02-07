#include "Winsock2.h"                
#pragma comment(lib, "WS2_32.lib") 
#include <ws2tcpip.h>
#include <chrono>

#include <iostream>
#include <string>

using namespace std;

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

bool  GetServer(char* call, short port, struct sockaddr* from, int* flen) {
    SOCKET sS;

    sS = socket(AF_INET, SOCK_DGRAM, NULL); //исп юдп
    if (sS == INVALID_SOCKET) {
        cout << "Ошибка при создании сокета: " << WSAGetLastError() << endl;
    }
    else {
        cout << "Сокет успешно создан." << endl;
    }

    SOCKADDR_IN broadcast_addr;
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(port);
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST; //широковещат аддрес

    int broadcast = 1;
    int sent_len;
    int recv_len;
    char buffer[50];

    if (setsockopt(sS, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) == SOCKET_ERROR) { //разрешаем широковещ сообщ
        throw SetErrorMsgText("Ошибка при установке размера буфера (setsockopt): ", WSAGetLastError());
        closesocket(sS);
    }


    int timeout = 20000;
    if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) == SOCKET_ERROR) { // уст таймаут
        closesocket(sS);
        throw SetErrorMsgText("Ошибка при установке времени ожидания (SO_RCVTIMEO): ", WSAGetLastError());
    }


    if (sent_len = sendto(sS, call, strlen(call), NULL, (sockaddr*)&broadcast_addr, sizeof(broadcast_addr)) == SOCKET_ERROR) {
        closesocket(sS);
        throw SetErrorMsgText("Ошибка при отправке сообщения (sendto):  ", WSAGetLastError());
    }
    else {
        cout << "Сообщение успешно отправлено." << endl;
    }

    memset(buffer, 0, sizeof(buffer));
    recv_len = recvfrom(sS, buffer, sizeof(buffer) - 1, NULL, from, flen);
    if (recv_len == SOCKET_ERROR) {
        closesocket(sS);
        if (WSAGetLastError() == WSAETIMEDOUT) {
            cout << "Время ожидания ответа от сервера истекло." << endl;
            return false;
        }
        else {
            throw SetErrorMsgText("Ошибка при получении сообщения (recvfrom): ", WSAGetLastError());
        }
    }
    else {
        cout << "Сообщение получено от сервера." << endl;
    }

    // Проверка соответствия полученного сообщения ожидаемому
    if (strcmp(buffer, call) == 0) {
        cout << "Полученное сообщение совпадает с ожидаемым." << endl;
        closesocket(sS);
        return true;
    }
    else {
        cout << "Полученное сообщение не совпадает с ожидаемым." << endl;
        closesocket(sS);
        return false;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    WSADATA wsaData;
    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Ошибка при вызове WSAStartup:", WSAGetLastError());

        sockaddr_in server_addr;  // параметры сервера
        int addr_len = sizeof(server_addr);  // размер структуры
        char name[] = "Hi,bro!";
        short port = 2000;
        if (GetServer(name, port, (sockaddr*)&server_addr, &addr_len))
        {
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(server_addr.sin_addr), ip, INET_ADDRSTRLEN);

            cout << "Подключенный сервер: " << endl;
            cout << "IP: " << ip << endl;
            cout << "Port: " << htons(server_addr.sin_port) << endl;; 
        }
        else {
            cout << "Ошибка при подключении к серверу\n";
        }

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("Ошибка при вызове WSACleanup:", WSAGetLastError());
        system("pause");
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }
    return 0;
}

