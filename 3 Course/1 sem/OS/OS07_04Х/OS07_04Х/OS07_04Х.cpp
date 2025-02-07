#include <Windows.h>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

// Проверка числа на простоту
bool isSimple(int n) {
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cerr << "Ошибка: не указано время работы процесса.\n";
        return 1;
    }

    // Считывание времени работы в секундах из аргумента командной строки
    int workTime = atoi(argv[1]);
    if (workTime <= 0) {
        cerr << "Ошибка: некорректное время работы.\n";
        return 1;
    }

    cout << "Дочерний процесс запущен. Время работы: " << workTime << " секунд.\n";

    clock_t start = clock();
    for (long long i = 2; ; i++) {
        if ((clock() - start) / CLOCKS_PER_SEC >= workTime) {
            cout << "Время работы истекло. Завершение процесса.\n";
            break;
        }
        if (isSimple(i)) {
            cout << i << '\n';
        }
    }
    cout << "Дочерний процесс завершён.\n";
    system("pause");
    return 0;
}