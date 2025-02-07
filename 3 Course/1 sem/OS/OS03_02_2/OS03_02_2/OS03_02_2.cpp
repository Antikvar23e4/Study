#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "Russian");

    DWORD pid = GetCurrentProcessId();
    std::cout << "Айди процесса OS_03_02_2: " << pid << std::endl;

    for (int i = 0; i < 125; i++) {
        std::cout << "Итерация OS_03_02_2: " << i + 1 << std::endl;
        Sleep(1000);
    }

    return 0;
}
