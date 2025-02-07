#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "Russian");

    DWORD pid = GetCurrentProcessId();
    std::cout << "Айди родительского процесса: " << pid << std::endl;

    // Создание 1 дочернего процесса
    STARTUPINFO si1 = { sizeof(si1) };
    PROCESS_INFORMATION pi1;

    if (CreateProcess(L"OS03_02_1.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1)) {
        std::cout << " OS03_02_1 started." << std::endl;
    }
    else {
        std::cerr << "Ошибка запуска OS03_02_1." << std::endl;
    }

    // Создание 2 дочернего процесса
    STARTUPINFO si2 = { sizeof(si2) };
    PROCESS_INFORMATION pi2;

    if (CreateProcess(L"OS03_02_2.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)) {
        std::cout << " OS03_02_2 started." << std::endl;
    }
    else {
        std::cerr << "Ошибка запуска OS03_02_2." << std::endl;
    }


    for (int i = 0; i < 100; i++) {
        std::cout << "Итерация родительского процееса: " << i + 1 << std::endl;
        Sleep(1000);
    }

    // Ожидание завершения дочерних процессов
    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);

    // Закрытие дескрипторов
    CloseHandle(pi1.hProcess);
    CloseHandle(pi1.hThread);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

    return 0;
}
