#include "pch.h"
#include "Auxil.h"
#include <iostream>
#include <ctime>
#include <locale>
using namespace std;

#define  CYCLE  300000                       // количество циклов  
int main()
{
	cout << "1-2 задание" << endl;
	double  av1 = 0, av2 = 0;
	clock_t  t1 = 0, t2= 0;
	setlocale(LC_ALL, "rus");

	auxil::start();                          // старт генерации 
	t1 = clock();                            // фиксация времени 
	for (int i = 0; i < CYCLE; i++)
	{
		av1 += (double)auxil::iget(-100, 100); // сумма случайных чисел 
		av2 += auxil::dget(-100, 100);         // сумма случайных чисел 
	}
	t2 = clock();                            // фиксация времени 


	std::cout << std::endl << "Количество циклов:         " << CYCLE;
	std::cout << std::endl << "Среднее значение (int):    " << av1 / CYCLE;
	std::cout << std::endl << "Среднее значение (double): " << av2 / CYCLE;
	std::cout << std::endl << "Продолжительность (у.е):   " << (t2 - t1);
	std::cout << std::endl << "                  (сек):   "
		<< ((double)(t2 - t1)) / ((double)CLOCKS_PER_SEC);
	std::cout << std::endl;
	system("pause");

	cout << "3 задание" << endl << endl;
	auxil::start(); // Инициализация генератора случайных чисел

	int n = 35;

	cout << "Генерация последовательности чисел Фибоначчи до " << n << " члена:\n";

	clock_t start = clock(); // Запуск таймера

	for (int i = 0; i < n; ++i)
	{
		int fib = auxil::fibonacci(i);
		cout << fib << " ";
	}

	clock_t end = clock(); // Остановка таймера

	cout << std::endl;

	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << "Время выполнения программы: " << time_taken << " секунд" << endl;
	return 0;

}