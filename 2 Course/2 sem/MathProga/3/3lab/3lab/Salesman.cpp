#include "stdafx.h"
#include "Salesman.h"

// Функция для сложения двух чисел с обработкой бесконечности (INF).
int sum(int x1, int x2)
{
    return (x1 == INF || x2 == INF) ? INF : (x1 + x2);
}

// Инициализация первого пути, пройденного коммивояжером.
int* firstpath(int n)
{
    int* rc = new int[n + 1];
    rc[n] = 0;
    for (int i = 0; i < n; i++)
        rc[i] = i;
    return rc;
}

// Инициализация массива источника для генерации перестановок.
int* source(int n)
{
    int* rc = new int[n - 1];
    for (int i = 1; i < n; i++)
        rc[i - 1] = i;
    return rc;
}

// Копирование пути из одного массива в другой.
void copypath(int n, int* r1, const int* r2)
{
    for (int i = 0; i < n; i++)
        r1[i] = r2[i];
}

// Расчет общего расстояния в пути по матрице расстояний.
int distance(int n, int* r, const int* d)
{
    int rc = 0;
    for (int i = 0; i < n - 1; i++)
        rc = sum(rc, d[r[i] * n + r[i + 1]]);
    return sum(rc, d[r[n - 1] * n + 0]);
}

// Индексация пути с использованием заданных сетов и номеров узлов.
void indx(int n, int* r, const int* s, const short* ntx)
{
    for (int i = 1; i < n; i++)
        r[i] = s[ntx[i - 1]];
}

// Основная функция поиска кратчайшего пути коммивояжера.
int salesman(int n, const int* d, int* r)
{
    int* s = source(n), * b = firstpath(n), rc = INF, dist = 0;
    combi::permutation p(n - 1);
    int k = p.getfirst();

    // Перебор всех перестановок и поиск оптимального пути.
    while (k >= 0)
    {
        indx(n, b, s, p.sset);
        if ((dist = distance(n, b, d)) < rc)
        {
            rc = dist;
            copypath(n, r, b);
        }
        k = p.getnext();
    };
    return rc;
}
