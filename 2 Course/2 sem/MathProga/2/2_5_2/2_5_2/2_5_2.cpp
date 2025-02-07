#include "pch.h"
#include <iostream>
#include <iomanip> 
#include "Boat.h"
#include <cstdlib> 
#include <ctime>   
#include <chrono>

#define NN 8
#define MM 8

int main()
{
    setlocale(LC_ALL, "rus");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int v[NN];// вес
    int c[NN];// доход 
    int minv[MM]; // минимальный  вес 
    int maxv[MM];// максимальный вес
    
    for (int i = 0; i < NN; i++) {
        v[i] = rand() % 101 + 100; // случайное значение от 100 до 200
        c[i] = rand() % 91 + 10;   // случайное значение от 10 до 100
    }

    for (int i = 0; i < MM; i++) {
        minv[i] = rand() % 71 + 50;  // случайное значение от 50 до 120
        maxv[i] = rand() % 701 + 150; // случайное значение от 150 до 850
    }
    
    auto start_time = std::chrono::high_resolution_clock::now();

    short r[MM];
    int cc = boat_с(
        MM,    // [in]  количество мест для контейнеров
        minv,  // [in]  максимальный вес контейнера на каждом  месте 
        maxv,  // [in]  минимальный вес контейнера на каждом  месте  
        NN,    // [in]  всего контейнеров  
        v,     // [in]  вес каждого контейнера  
        c,     // [in]  доход от перевозки каждого контейнера   
        r      // [out] номера  выбранных контейнеров  
    );
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << std::endl << "- Задача о размещении контейнеров на судне -";
    std::cout << std::endl << "- общее количество контейнеров   : " << NN;
    std::cout << std::endl << "- количество мест для контейнеров  : " << MM;
    std::cout << std::endl << "- минимальный  вес контейнера  : ";
    for (int i = 0; i < MM; i++) std::cout << std::setw(3) << minv[i] << " ";
    std::cout << std::endl << "- максимальный вес контейнера  : ";
    for (int i = 0; i < MM; i++) std::cout << std::setw(3) << maxv[i] << " ";
    std::cout << std::endl << "- вес контейнеров      : ";
    for (int i = 0; i < NN; i++) std::cout << std::setw(3) << v[i] << " ";
    std::cout << std::endl << "- доход от перевозки     : ";
    for (int i = 0; i < NN; i++) std::cout << std::setw(3) << c[i] << " ";
    std::cout << std::endl << "- выбраны контейнеры (0,1,...,m-1) : ";
    for (int i = 0; i < MM; i++) std::cout << r[i] << " ";
    std::cout << std::endl << "- доход от перевозки     : " << cc;
    std::cout << std::endl << std::endl;
    std::cout << "Время выполнения: " << duration.count() << " микросекунд." << std::endl;
    system("pause");
    return 0;
}
