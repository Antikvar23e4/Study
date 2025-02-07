#include <iostream>
#include <ctime>
#include <iomanip>  // Для форматирования вывода

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    // Получаем текущее время
    time_t now = time(0);

    // Преобразуем в локальное время
    struct tm ttm;
    localtime_s(&ttm, &now);

    cout << "Текущая дата и время: "
        << setfill('0')  // для заполнения пустых значений
        << setw(2) << ttm.tm_mday << "."
        << setw(2) << ttm.tm_mon + 1 << "."  // Месяцы начинаются с 0, добавляем 1
        << setw(4) << ttm.tm_year + 1900 << " "  // Год начинается с 1900, добавляем 1900
        << setw(2) << ttm.tm_hour << ":"
        << setw(2) << ttm.tm_min << ":"
        << setw(2) << ttm.tm_sec << endl;
    //или
    cout << put_time(&ttm, "%d.%m.%Y %H:%M:%S") << endl;
    return 0;
}
