#include <iostream>
#include "Winsock2.h"                // заголовок  WS2_32.dll
#include <string>
#pragma comment(lib, "WS2_32.lib")   // экспорт  WS2_32.dll

#pragma warning(disable: 4996)  

using namespace std;

string GetErrorMsgText(int code)    
{
    string msgText;
    switch (code)                     
    {
    case WSAEINTR:          msgText = "WSAEINTR: Работа функции прервана"; break;
    case WSAEACCES:         msgText = "WSAEACCES: Разрешение отвергнуто"; break;
    case WSAEFAULT:         msgText = "WSAEFAULT: Ошибочный адрес"; break;
    case WSAEINVAL:         msgText = "WSAEINVAL: Ошибка в аргументе"; break;
    case WSAEMFILE:         msgText = "WSAEMFILE: Слишком много файлов открыто"; break;
    case WSAEWOULDBLOCK:    msgText = "WSAEWOULDBLOCK: Ресурс временно недоступен"; break;
    case WSAEINPROGRESS:    msgText = "WSAEINPROGRESS: Операция в процессе развития"; break;
    case WSAEALREADY:       msgText = "WSAEALREADY: Операция уже выполняется"; break;
    case WSAENOTSOCK:       msgText = "WSAENOTSOCK: Сокет задан неправильно"; break;
    case WSAEDESTADDRREQ:   msgText = "WSAEDESTADDRREQ: Требуется адрес расположения"; break;
    case WSAEMSGSIZE:       msgText = "WSAEMSGSIZE: Сообщение слишком длинное"; break;
    case WSAEPROTOTYPE:     msgText = "WSAEPROTOTYPE: Неправильный тип протокола для сокета"; break;
    default:                msgText = "***ERROR***: Unknown error"; break;
    }
    return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
    return msgText + " " + GetErrorMsgText(code);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    WSADATA wsaData;
    SOCKET sS; // сокет сервера

    SOCKADDR_IN servAddr;  // структура  адреса сервера
    int port = 2000;  // порт 

    try
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw SetErrorMsgText("Ошибка при вызове WSAStartup: ", WSAGetLastError());
        }
        cout << "Winsock библиотека инициализирована." << endl;

        if ((sS = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            throw SetErrorMsgText("Ошибка при создании сокета: ", WSAGetLastError());
        }
        cout << "Сокет создан." << endl;

        //   SOCKADDR_IN 
        servAddr.sin_family = AF_INET;                // семейство адресов IPv4
        servAddr.sin_port = htons(port);              // порт (переводим в сетевой порядок байтов)
        servAddr.sin_addr.s_addr = INADDR_ANY;        // принимаем соединения с любых адресов

        // Привязка сокета к IP-адресу и порту
        if (bind(sS, (LPSOCKADDR)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при привязке сокета (bind): ", WSAGetLastError());
        }
        cout << "Сокет успешно привязан к порту " << port << "." << endl;

        // Перевод сокета в режим прослушивания
        if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при переводе сокета в режим прослушивания (listen): ", WSAGetLastError());
        }
        cout << "Сокет переведен в режим прослушивания." << endl;

        while (true) // цикл для работы с несколькими клиентами
        {
            SOCKET cS;        // сокет клиента
            SOCKADDR_IN clntAddr;  // структура  адреса клиента
            int addrLen = sizeof(clntAddr);  // размер структуры clntAddr

            // Принимаем соединение
            if ((cS = accept(sS, (sockaddr*)&clntAddr, &addrLen)) == INVALID_SOCKET)
            {
                cerr << "Ошибка при принятии подключения (accept): " << SetErrorMsgText("", WSAGetLastError()) << endl;
                continue; 
            }

            cout << "Клиент подключился." << endl;
            cout << "IP клиента: " << inet_ntoa(clntAddr.sin_addr) << endl;
            cout << "Порт клиента: " << ntohs(clntAddr.sin_port) << endl;

            char buffer[256]; // Буфер для получения данных
            int bytesReceived;

            // Обрабатываем сообщения от клиента
            while ((bytesReceived = recv(cS, buffer, sizeof(buffer), 0)) > 0)
            {
                buffer[bytesReceived] = '\0'; // Завершаем строку
                cout << "Получено сообщение: " << buffer << endl;

                // Отправляем сообщение обратно клиенту
                if (send(cS, buffer, bytesReceived, 0) == SOCKET_ERROR)
                {
                    cerr << "Ошибка при отправке сообщения: " << SetErrorMsgText("", WSAGetLastError()) << endl;
                    break; 
                }
            }
            if (closesocket(cS) == SOCKET_ERROR)
            {
                cerr << "Ошибка при закрытии клиентского сокета: " << SetErrorMsgText("", WSAGetLastError()) << endl;
            }
            cout << "Клиентский сокет закрыт." << endl;
        }

        if (closesocket(sS) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при закрытии сокета: ", WSAGetLastError());
        }
        cout << "Сокет закрыт." << endl;

        if (WSACleanup() == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при вызове WSACleanup: ", WSAGetLastError());
        }
        cout << "Winsock библиотека завершила работу." << endl;
    }
    catch (string errorMsgText)
    {
        cout << endl << "Ошибка: " << errorMsgText << endl;
    }
    return 0;
}
