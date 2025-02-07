#include "stdafx.h"
#include <iomanip>
#include <algorithm>
#include "Levenshtein.h"

// Макрос для удобного доступа к ячейкам матрицы расстояний
#define DD(i,j) d[(i)*(ly+1)+(j)] 

// Функция для нахождения минимума из трех чисел
int min3(int x1, int x2, int x3)
{
    return std::min(std::min(x1, x2), x3);
}

// Функция для вычисления расстояния Левенштейна с помощью динамического программирования
int levenshtein(int lx, const char x[], int ly, const char y[])
{
    // Выделение памяти под матрицу расстояний
    int* d = new int[(lx + 1) * (ly + 1)];

    // Инициализация нулевой строки и нулевого столбца
    for (int i = 0; i <= lx; i++) DD(i, 0) = i;
    for (int j = 0; j <= ly; j++) DD(0, j) = j;

    // Заполнение матрицы расстояний
    for (int i = 1; i <= lx; i++)
        for (int j = 1; j <= ly; j++)
        {
            DD(i, j) = min3(DD(i - 1, j) + 1, DD(i, j - 1) + 1,
                DD(i - 1, j - 1) + (x[i - 1] == y[j - 1] ? 0 : 1));
        }

    // Возвращаем значение расстояния для последних символов
    return DD(lx, ly);
}

// Рекурсивная функция для вычисления расстояния Левенштейна
int levenshtein_r(
    int lx, const char x[],
    int ly, const char y[]
)
{
    int rc = 0;
    // Базовые случаи
    if (lx == 0) rc = ly;
    else if (ly == 0) rc = lx;
    else if (lx == 1 && ly == 1 && x[0] == y[0]) rc = 0;
    else if (lx == 1 && ly == 1 && x[0] != y[0]) rc = 1;
    // Рекурсивный случай
    else rc = min3(
        levenshtein_r(lx - 1, x, ly, y) + 1,
        levenshtein_r(lx, x, ly - 1, y) + 1,
        levenshtein_r(lx - 1, x, ly - 1, y) + (x[lx - 1] == y[ly - 1] ? 0 : 1)
    );
    return rc;
};
