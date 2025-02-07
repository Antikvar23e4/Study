#include <iostream>
#include <windows.h>

using namespace std;

CRITICAL_SECTION critical_section;

DWORD WINAPI loop(LPVOID param) {
    char* displayed_name = static_cast<char*>(param);
    int pid = GetCurrentProcessId();
    int tid = GetCurrentThreadId();

    for (int i = 1; i <= 90; ++i) {
        if (i == 30) {
            EnterCriticalSection(&critical_section);
            printf("\n[%s] ВХОД В КРИТИЧЕСКУЮ СЕКЦИЮ (итерация %d)\n", displayed_name, i);
        }

        printf("[%s]\tИтерация: %d\tPID: %d\tTID: %u\n", displayed_name, i, pid, tid);

        if (i == 60) {
            printf("[%s] ВЫХОД ИЗ КРИТИЧЕСКОЙ СЕКЦИИ (итерация %d)\n\n", displayed_name, i);
            LeaveCriticalSection(&critical_section);
        }
        Sleep(100);
    }

    printf("\n=================  %s ЗАВЕРШИЛСЯ  =================\n\n", displayed_name);
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int pid = GetCurrentProcessId();
    const int size = 2;
    HANDLE threads[size];

    InitializeCriticalSection(&critical_section);

    threads[0] = CreateThread(NULL, 0, loop, (LPVOID)"A", 0, NULL);
    if (threads[0] == NULL) throw "[ERROR] CreateThread A";

    threads[1] = CreateThread(NULL, 0, loop, (LPVOID)"B", 0, NULL);
    if (threads[1] == NULL) throw "[ERROR] CreateThread B";

    for (int i = 1; i <= 90; ++i) {
        if (i == 30) {
            EnterCriticalSection(&critical_section);
            printf("\n[MAIN] ВХОД В КРИТИЧЕСКУЮ СЕКЦИЮ (итерация %d)\n", i);
        }

        printf("[MAIN]\tИтерация: %d\tPID: %d\n", i, pid);

        if (i == 60) {
            printf("[MAIN] ВЫХОД ИЗ КРИТИЧЕСКОЙ СЕКЦИИ (итерация %d)\n\n", i);
            LeaveCriticalSection(&critical_section);
        }

        Sleep(100);
    }

    printf("\n=================  MAIN ЗАВЕРШИЛСЯ  =================\n\n");

    WaitForMultipleObjects(size, threads, TRUE, INFINITE);
    for (int i = 0; i < size; ++i)
        CloseHandle(threads[i]);

    DeleteCriticalSection(&critical_section);
    return 0;
}
