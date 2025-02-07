#include <iostream>
#include "Winsock2.h"
#include <string>
#include <ctime>
#include <thread> // Для использования std::this_thread::sleep_for
#include <chrono> // Для использования std::chrono::seconds
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
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

string SetErrorMsgText(string msgText, int code) {
    return msgText + " " + GetErrorMsgText(code);
}

int main() {
    setlocale(LC_ALL, "Russian");
    WSADATA wsaData;
    SOCKET cC;
    SOCKADDR_IN servAddr;
    char bto[50];
    char bfrom[50];
    int port = 2000;
    int send_len = 0;
    int numMessages;

    cout << "Введите уникальный номер клиента: ";
    int clientId;
    cin >> clientId; 

    cout << "Введите количество сообщений для отправки: ";
    cin >> numMessages; 

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw SetErrorMsgText("Ошибка при вызове WSAStartup: ", WSAGetLastError());
    }
    cout << "Winsock библиотека инициализирована." << endl;

    if ((cC = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        throw SetErrorMsgText("Ошибка при создании сокета: ", WSAGetLastError());
    }
    cout << "Сокет создан." << endl;

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = inet_addr("26.167.5.245"); //26.69.212.139 
    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i <= numMessages; ++i) {
        strcpy(bto, "Hello");  // Изменено сообщение на "Hello"

        if ((send_len = sendto(cC, bto, strlen(bto), 0, (sockaddr*)&servAddr, sizeof(servAddr))) == SOCKET_ERROR) {
            throw SetErrorMsgText("Ошибка при отправке сообщения (sendto): ", WSAGetLastError());
        }
        cout << "Сообщение отправлено: " << bto << endl;
        Sleep(1);

        //закоменчено для потери пакетов
        sockaddr_in from;
        int fromlen = sizeof(from);
        int recv_len;

        if ((recv_len = recvfrom(cC, bfrom, sizeof(bfrom), 0, (sockaddr*)&from, &fromlen)) == SOCKET_ERROR) {
            throw SetErrorMsgText("Ошибка при получении сообщения (recvfrom): ", WSAGetLastError());
        }

        bfrom[recv_len] = '\0';
        cout << "Получено сообщение от сервера: " << bfrom << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Общее время отправки " << numMessages << " сообщений: " << elapsed.count() << " секунд." << endl;

    if (closesocket(cC) == SOCKET_ERROR) {
        throw SetErrorMsgText("Ошибка при закрытии сокета: ", WSAGetLastError());
    }
    cout << "Сокет закрыт." << endl;

    if (WSACleanup() == SOCKET_ERROR) {
        throw SetErrorMsgText("Ошибка при вызове WSACleanup: ", WSAGetLastError());
    }
    cout << "Winsock библиотека завершила работу." << endl;

    return 0;
}
