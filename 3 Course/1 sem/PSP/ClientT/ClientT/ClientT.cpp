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
    };
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
    SOCKET sC; 

    SOCKADDR_IN servAddr;  
    const char* serverIp = "127.0.0.1"; //задание 12 - поменять айпи
    int port = 2000;  

    try
    {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            throw SetErrorMsgText("Ошибка при вызове WSAStartup: ", WSAGetLastError());
        }
        cout << "Winsock библиотека инициализирована." << endl;

        if ((sC = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
        {
            throw SetErrorMsgText("Ошибка при создании сокета: ", WSAGetLastError());
        }
        cout << "Сокет клиента создан." << endl;

        servAddr.sin_family = AF_INET;                // семейство адресов IPv4
        servAddr.sin_port = htons(port);              // порт (переводим в сетевой порядок байтов)
        servAddr.sin_addr.s_addr = inet_addr(serverIp); // адрес сервера

        if (connect(sC, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при подключении к серверу (connect): ", WSAGetLastError());
        }
        cout << "Подключено к серверу." << endl;

        int count;
        cout << "Введите количество сообщений для передачи: ";
        cin >> count;

        char message[50];
        int messageNumber = 1;

        clock_t startTime = clock();

        for (int i = 0; i < count; ++i) {
            sprintf(message, "Hello from Client %d", messageNumber);
            if (send(sC, message, strlen(message) + 1, 0) == SOCKET_ERROR) {
                throw SetErrorMsgText("Ошибка при отправке сообщения (send): ", WSAGetLastError());
            }
            cout << "Отправлено сообщение: " << message << endl;

            char buffer[50];
            if (recv(sC, buffer, sizeof(buffer), 0) == SOCKET_ERROR) {
                throw SetErrorMsgText("Ошибка при получении ответа от сервера (recv): ", WSAGetLastError());
            }

            cout << "Ответ от сервера: " << buffer << endl;
            messageNumber++;
        }
        // Отправка сообщения нулевой длины для завершения работы сервера
        send(sC, "", 0, 0);

        clock_t endTime = clock();
        double elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC; 
        cout << "Обмен сообщениями занял: " << elapsedTime << " секунд." << endl;

        if (closesocket(sC) == SOCKET_ERROR)
        {
            throw SetErrorMsgText("Ошибка при закрытии сокета клиента: ", WSAGetLastError());
        }
        cout << "Сокет клиента закрыт." << endl;

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
