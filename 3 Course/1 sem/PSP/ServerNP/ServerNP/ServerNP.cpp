#include <windows.h>
#include <iostream>

using namespace std;

void HandleError(const char* message) {
    DWORD errorCode = GetLastError();
    cerr << message << " (Код ошибки: " << errorCode << ")" << endl;
}

HANDLE CreateNamedPipe() {
    HANDLE hPipe = CreateNamedPipeA(
        "\\\\.\\pipe\\Tube",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        0,
        0,
        INFINITE,
        nullptr
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        HandleError("Ошибка при создании канала.");
    }
    return hPipe;
}

void ExchangeMessages(HANDLE hPipe) {
    char rbuf[128];
    DWORD bytesRead, bytesWritten;

    while (true) {
        if (ReadFile(hPipe, rbuf, sizeof(rbuf) - 1, &bytesRead, nullptr)) {
            rbuf[bytesRead] = '\0';
            if (bytesRead == 1 && rbuf[0] == '\0') {
                cout << "Получено сообщение нулевой длины. Завершение работы сервера." << endl;
                break;
            }

            cout << "Получено сообщение от клиента: " << rbuf << endl;

            // отправка сообщения обратно клиенту
            if (!WriteFile(hPipe, rbuf, bytesRead, &bytesWritten, nullptr)) {
                HandleError("Ошибка при записи в канал.");
                break;
            }
        }
        else {
            cout << "Клиент закрыл соединение." << endl;
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        HANDLE hPipe = CreateNamedPipe();
        if (hPipe == INVALID_HANDLE_VALUE) {
            return 1;
        }

        cout << "Ожидание подключения клиента..." << endl;

        if (ConnectNamedPipe(hPipe, nullptr) || GetLastError() == ERROR_PIPE_CONNECTED) {
            cout << "Клиент подключен." << endl;
            ExchangeMessages(hPipe);
        }
        else {
            HandleError("Ошибка при подключении к каналу.");
        }

        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
        cout << "Дескриптор канала закрыт. Ожидание нового подключения..." << endl;
    }

    return 0;
}
