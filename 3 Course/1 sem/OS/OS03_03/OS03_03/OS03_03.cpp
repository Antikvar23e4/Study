#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

void ListProcesses() {
    // Создаем снимок всех процессов в системе
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cout << "Ошибка." << std::endl;
        return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Получаем информацию о первом процессе
    if (!Process32First(hProcessSnap, &pe32)) {
        std::cout << "Ошибка." << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    // Перебираем все процессы
    do {
        std::wcout << L"ID: " << pe32.th32ProcessID << L"\tProcess Name: " << pe32.szExeFile << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "Russian");

    ListProcesses();
    std::cin.get();
    return 0;
}
