#include "pch.h"
#include <iostream>
#include <iomanip>
#include "Boat.h"
#include <cstdlib> 

#define NN 8 
#define MM 5

void fillArraysRandomly(int* v, int* c, int size) {
    for (int i = 0; i < size; ++i) {
        v[i] = rand() % 101 + 100; // Вес контейнера от 100 до 200 кг
        c[i] = rand() % 91 + 10;    // Доход от перевозки от 10 до 100 у.е.
        // Проверяем условия минимального и максимального веса
        while (v[i] < 50 || v[i] > 120) {
            v[i] = rand() % 101 + 100;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int V = 1000,
        v[NN],
        c[NN]; 
    short  r[MM];

    // Заполнение массивов случайными числами
    fillArraysRandomly(v, c, NN);

    int cc = boat(
        V,   // [in]  максимальный вес груза
        MM,  // [in]  количество мест для контейнеров     
        NN,  // [in]  всего контейнеров  
        v,   // [in]  вес каждого контейнера  
        c,   // [in]  доход от перевозки каждого контейнера     
        r    // [out] результат: индексы выбранных контейнеров  
    );
    std::cout << std::endl << "- Задача о размещении контейнеров на судне";
    std::cout << std::endl << "- общее количество контейнеров    : " << NN;
    std::cout << std::endl << "- количество мест для контейнеров : " << MM;
    std::cout << std::endl << "- ограничение по суммарному весу  : " << V;
    std::cout << std::endl << "- вес контейнеров                 : ";
    for (int i = 0; i < NN; i++) std::cout << std::setw(3) << v[i] << " ";
    std::cout << std::endl << "- доход от перевозки              : ";
    for (int i = 0; i < NN; i++) std::cout << std::setw(3) << c[i] << " ";
    std::cout << std::endl << "- выбраны контейнеры (0,1,...,m-1): ";
    for (int i = 0; i < MM; i++) std::cout << r[i] << " ";
    std::cout << std::endl << "- доход от перевозки              : " << cc;
    std::cout << std::endl << "- общий вес выбранных контейнеров : ";
    int s = 0; for (int i = 0; i < MM; i++) s += v[r[i]]; std::cout << s;
    std::cout << std::endl << std::endl;
    system("pause");
    return 0;
}
