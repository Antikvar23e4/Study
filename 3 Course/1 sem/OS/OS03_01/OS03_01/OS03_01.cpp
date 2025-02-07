#include <windows.h>
#include <iostream>
#include <locale> 

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "Russian");

    DWORD processId = GetCurrentProcessId();

    std::cout << "Process ID: " << processId << std::endl;

    for (int i = 0; i < 1000000000000; ++i) {
        std::cout << "Номер итерации: " << i + 1<< std::endl;
        Sleep(1000);
    }

    std::cout << "Процесс заверешен" << std::endl;
    return 0;
}
