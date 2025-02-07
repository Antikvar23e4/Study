#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
    int pid = GetCurrentProcessId();
    const int size = 2;
    HANDLE semaphore;
    HANDLE processes[size] = { NULL, NULL };

    STARTUPINFO startupInfoA, startupInfoB;
    PROCESS_INFORMATION processInfoA, processInfoB;
    ZeroMemory(&startupInfoA, sizeof(STARTUPINFO));
    startupInfoA.cb = sizeof(STARTUPINFO);
    ZeroMemory(&startupInfoB, sizeof(STARTUPINFO));
    startupInfoB.cb = sizeof(STARTUPINFO);

    if (CreateProcessW(L"D:\\University\\1sem\\ОС\\OS06_04A\\x64\\Debug\\OS06_04A.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfoA, &processInfoA)) {
        cout << "Process A created\n";
        processes[0] = processInfoA.hProcess;
    }
    else cout << "[ERROR] CreateProcessW for Process A\n";
    if (CreateProcessW(L"D:\\University\\1sem\\ОС\\OS06_04B\\x64\\Debug\\OS06_04B.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfoB, &processInfoB)) {
        cout << "Process B created\n";
        processes[1] = processInfoB.hProcess;
    }
    else cout << "[ERROR] CreateProcessW for Process B\n";

    semaphore = CreateSemaphore(NULL, 2, 2, L"OS06_04");

    for (int i = 1; i <= 90; ++i) {
        if (i == 30) WaitForSingleObject(semaphore, INFINITE);
        else if (i == 60) ReleaseSemaphore(semaphore, 1, NULL);

        printf("[OS06_04]\t%d\tPID = %d\n", i, pid);
        Sleep(100);
    }

    WaitForMultipleObjects(size, processes, TRUE, INFINITE);

    CloseHandle(processInfoA.hProcess);
    CloseHandle(processInfoA.hThread);
    CloseHandle(processInfoB.hProcess);
    CloseHandle(processInfoB.hThread);

    if (semaphore) CloseHandle(semaphore);
    cout << '\n';
    system("pause");
    return 0;
}
