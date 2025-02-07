#include "pch.h"
#include "Auxil.h"

namespace auxil
{
    void start()                          // старт  генератора случайных чисел чисел
    {
        srand((unsigned)time(NULL));      // установка начального состояния генератора
    };
    double dget(double rmin, double rmax) // получить случайное число
    {
        return ((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin; // смещаем случайное число до нашего диапозона
    };
    int iget(int rmin, int rmax)         // получить случайное число

    {
        return (int)dget((double)rmin, (double)rmax);
    };

    // Функция для генерации чисел Фибоначчи
    int fibonacci(int n)
    {
        if (n <= 0)
            return 0;
        else if (n == 1)
            return 1;
        else
            return fibonacci(n - 1) + fibonacci(n - 2);
    }
}