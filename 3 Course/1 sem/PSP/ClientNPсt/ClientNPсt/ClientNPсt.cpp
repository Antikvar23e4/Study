#include <windows.h>
#include <iostream>
#include <string>
#include <ctime> 

using namespace std;

const int BUFFER_SIZE = 128; 

string SetPipeError(const char* message, DWORD errorCode) {
    return string(message) + " (Код ошибки: " + to_string(errorCode) + ")";
}

void WaitForPipe(const char* pipeName) {
    if (!WaitNamedPipeA(pipeName, NMPWAIT_WAIT_FOREVER)) {
        throw SetPipeError("Ошибка при ожидании подключения:", GetLastError());
    }
}

void SendMessageToPipe(const char* pipeName) {
    char buffer[BUFFER_SIZE], answer[BUFFER_SIZE];
    DWORD dwRead, dwWritten;

    string message = "Hello from Client";
    strncpy_s(buffer, message.c_str(), BUFFER_SIZE);
    clock_t start = clock(); 

    //CallNamedPipe 
    if (!CallNamedPipeA(pipeName, buffer, strlen(buffer) + 1, answer, BUFFER_SIZE, &dwRead, 1000)) {
        cerr << SetPipeError("Ошибка в CallNamedPipe:", GetLastError()) << endl;
        return;
    }
    else {
        cout << "Получен ответ от сервера: " << answer << endl; 
    }

    clock_t end = clock();
    double timeSpent = double(end - start) / CLOCKS_PER_SEC;
    cout << "Время передачи сообщения: " << timeSpent << " секунд\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    const char* pipeName = "\\\\.\\pipe\\Tube";

    try {
        WaitForPipe(pipeName); 
        SendMessageToPipe(pipeName); 
    }
    catch (const string& errorPipeText) {
        cout << endl << errorPipeText;
    }

    return 0;
}
