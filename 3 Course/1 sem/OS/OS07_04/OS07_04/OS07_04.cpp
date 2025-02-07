#include <Windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    DWORD pid = GetCurrentProcessId();
    cout << "ID основного процесса: " << pid << "\n";
    LPCWSTR path = L"D:\\University\\1sem\\ОС\\OS07_04Х\\x64\\Debug\\OS07_04Х.exe";

    wchar_t args1[] = L" 60"; // 1 минута работы
    wchar_t args2[] = L" 120"; // 2 минуты работы

    PROCESS_INFORMATION pi1, pi2;

    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(path, args1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi1)) {
            cout << "Дочерний процесс OS07_04_X #1 успешно создан (работа: 1 минута)\n";
        }
        else {
            cerr << "Ошибка: не удалось создать дочерний процесс OS07_04_X #1\n";
        }
    }

    {
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        if (CreateProcess(path, args2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi2)) {
            cout << "Дочерний процесс OS07_04_X #2 успешно создан (работа: 2 минуты)\n";
        }
        else {
            cerr << "Ошибка: не удалось создать дочерний процесс OS07_04_X #2\n";
        }
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    cout << "Дочерний процесс OS07_04_X #1 завершён\n";
    WaitForSingleObject(pi2.hProcess, INFINITE);
    cout << "Дочерний процесс OS07_04_X #2 завершён\n";

    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    cout << "Основной процесс завершён\n";
    return 0;
}