#include <windows.h>
#include <iostream>
#include <ctime>  
#include <string>


using namespace std;

void HandleError(const char* message) {
    DWORD errorCode = GetLastError();
    cerr << message << " (Код ошибки: " << errorCode << ")" << endl;
}

HANDLE CreatePipeConnection(const char* pipeName) {
    HANDLE hPipe = CreateFileA(
        pipeName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        HandleError("Ошибка при создании подключения.");
    }
    return hPipe;
}

void ExchangeMessages(HANDLE hPipe, int messageCount) {
    char rbuf[128];
    DWORD bytesRead, bytesWritten;

    clock_t start = clock();

    for (int i = 0; i < messageCount; ++i) {
        string message = "Hello from Client " + to_string(i);
        if (!WriteFile(hPipe, message.c_str(), message.size() + 1, &bytesWritten, nullptr)) {
            HandleError("Ошибка при записи в канал.");
            return;
        }

        if (!ReadFile(hPipe, rbuf, sizeof(rbuf) - 1, &bytesRead, nullptr)) {
            HandleError("Ошибка при чтении из канала.");
            return;
        }

        rbuf[bytesRead] = '\0';  
        cout << "Получено сообщение от сервера: " << rbuf << endl;
    }

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Время передачи " << messageCount << " сообщений: " << duration << " секунд" << endl;

    WriteFile(hPipe, "", 1, &bytesWritten, nullptr);
}

int main() {
    setlocale(LC_ALL, "Russian");
    const char* pipeName = "\\\\DESKTOP-IB5TTO9\\pipe\\Tube"; // путь к нашему каналу
    int messageCount;

    cout << "Введите количество сообщений для отправки: ";
    cin >> messageCount;

    HANDLE hPipe = CreatePipeConnection(pipeName);
    if (hPipe == INVALID_HANDLE_VALUE) {
        return 1;
    }
    cout << "Подключение к каналу успешно." << endl;

    ExchangeMessages(hPipe, messageCount);

    CloseHandle(hPipe);
    cout << "Дескриптор канала закрыт." << endl;

    return 0;
}
