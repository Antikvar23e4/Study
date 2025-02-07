#include <iostream>
#include <windows.h>  

using namespace std;

DWORD WINAPI OS04_02_T1(LPVOID) {
    DWORD processId = GetCurrentProcessId();  
    DWORD threadId = GetCurrentThreadId();    

    for (int i = 0; i < 50; ++i) {
        cout << "Поток 1 (ID процесса: " << processId << ", ID потока: " << threadId
            << "), итерация: " << i + 1 << endl;
        Sleep(1000);  
    }
    return 0;
}

DWORD WINAPI OS04_02_T2(LPVOID) {
    DWORD processId = GetCurrentProcessId();  
    DWORD threadId = GetCurrentThreadId(); 

    for (int i = 0; i < 125; ++i) {
        cout << "Поток 2 (ID процесса: " << processId << ", ID потока: " << threadId
            << ")  итерация: " << i + 1 << endl;
        Sleep(1000);
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");

    DWORD processId = GetCurrentProcessId();

    HANDLE hThread1 = CreateThread(NULL, 0, OS04_02_T1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, OS04_02_T2, NULL, 0, NULL);

    if (hThread1 == NULL || hThread2 == NULL) {
        cerr << "Ошибка при создании потоков." << endl;
        return 1;
    }

    for (int i = 0; i < 100; ++i) {
        cout << "ID процесса: " << processId << " | Итерация основного потока: " << i + 1 << endl;
        Sleep(1000);  // Задержка 1 секунда
    }
    // Ожидание завершения потоков
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    // Закрытие дескрипторов потоков
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    return 0;
}
