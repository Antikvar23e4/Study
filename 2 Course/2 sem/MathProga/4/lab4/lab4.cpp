#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include "stdafx.h"
#include <algorithm>
#include <iomanip>
#include "Levenshtein.h"
#include <cmath>
#include <memory.h>
#include "MultyMatrix.h"   
#include <chrono>

using namespace std;
#define _rand(min, max) ( rand() % ((max) - (min) + 1) + (min) )
#define N 6

// Функция для замера времени выполнения метода OptimalM
double measureTimeOptimalM(const int* Mc) {
    auto start = std::chrono::high_resolution_clock::now(); // Замер времени начала выполнения
    int Ms[N][N];
    int r = OptimalM(1, N, N, Mc, OPTIMALM_PARM(Ms)); // Вызов рекурсивной функции
    auto end = std::chrono::high_resolution_clock::now(); // Замер времени окончания выполнения
    std::chrono::duration<double> elapsed = end - start; // Вычисление времени выполнения в секундах
    return elapsed.count() * 1000; // Возвращаем время в миллисекундах
}

// Функция для замера времени выполнения метода OptimalMD
double measureTimeOptimalMD(const int* Mc) {
    auto start = std::chrono::high_resolution_clock::now(); // Замер времени начала выполнения
    int Ms[N][N];
    int rd = OptimalMD(N, Mc, OPTIMALM_PARM(Ms)); // Вызов функции динамического программирования
    auto end = std::chrono::high_resolution_clock::now(); // Замер времени окончания выполнения
    std::chrono::duration<double> elapsed = end - start; // Вычисление времени выполнения в секундах
    return elapsed.count() * 1000; // Возвращаем время в миллисекундах
}

string generateRandomString(int length) {
    string result;
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Инициализация генератора случайных чисел
    mt19937 rng(time(nullptr));
    uniform_int_distribution<int> dist(0, sizeof(charset) - 2);

    for (int i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");

    cout << "1 задание" << endl;
    srand(time(NULL));
    char abc[25];
    char s1[300];
    char s2[250];

    for (int i = 97, n = 0; i <= 122; ++i, ++n)
    {
        abc[n] = (char)i;
    }
    cout << "S1 = ";
    for (int i = 0; i < 301; i++)
    {
        s1[i] = abc[_rand(0, 25)];
        if (i % 50 == 0)
            cout << "\n";
        cout << s1[i];
    }

    cout << "\nS2 =";
    for (int i = 0; i < 251; i++)
    {
        s2[i] = abc[_rand(0, 25)];
        if (i % 50 == 0)
            cout << "\n";
        cout << s2[i];
    }
    cout << "\n";

    cout << "5 задание" << endl;
    int Mc[N + 1] = { 8, 11, 19, 22, 29, 39, 50 }, Ms[N][N], r = 0, rd = 0;

    memset(Ms, 0, sizeof(int) * N * N);
    r = OptimalM(1, N, N, Mc, OPTIMALM_PARM(Ms));
    setlocale(LC_ALL, "rus");
    cout << endl << "-- расстановка скобок (рекурсивное решение) "
        << endl;
    cout << endl << "размерности матриц: ";
    for (int i = 1; i <= N; i++) cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
    cout << endl << "минимальное количество операций умножения: " << r;
    cout << endl << endl << "матрица S" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N; j++)  cout << Ms[i][j] << "  ";
    }
    cout << endl;

    memset(Ms, 0, sizeof(int) * N * N);
    rd = OptimalMD(N, Mc, OPTIMALM_PARM(Ms));
    cout << endl
        << "-- расстановка скобок (динамичеое программирование) " << endl;
    cout << endl << "размерности матриц: ";
    for (int i = 1; i <= N; i++)
        cout << "(" << Mc[i - 1] << "," << Mc[i] << ") ";
    cout << endl << "минимальное количество операций умножения: "
        << rd;
    cout << endl << endl << "матрица S" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N; j++)  cout << Ms[i][j] << "  ";
    }
    cout << endl << endl;
    double timeRecursive = measureTimeOptimalM(Mc);
    std::cout << "Время выполнения рекурсивного метода: " << timeRecursive << " секунд" << std::endl;

    // Измерение времени для метода динамического программирования
    double timeDynamic = measureTimeOptimalMD(Mc);
    std::cout << "Время выполнения метода динамического программирования: " << timeDynamic << " секунд" << std::endl;

    cout << "2 задание" << endl;
    clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    int lx = sizeof(s1);
    int ly = sizeof(s2);


    int S1_size[]{ 6,7,8,9,10,11 };
    int S2_size[]{ 8,9,10,11,12,13 };


    cout << "\n\n-- расстояние Левенштейна -----";
    cout << "\n\n--длина --- рекурсия -- дин.програм. ---\n";

    for (int i = 0; i < min(lx, ly); i++)
    {
        t1 = clock();
        levenshtein_r(S1_size[i], s1, S2_size[i], s2);
        t2 = clock();

        t3 = clock();
        levenshtein(S1_size[i], s1, S2_size[i], s2);
        t4 = clock();
        cout << right << setw(2) << S1_size[i] << "/" << setw(2) << S2_size[i]
            << "        " << left << setw(10) << (t2 - t1)
            << "   " << setw(10) << (t4 - t3) << endl;
    }

    return 0;
}
