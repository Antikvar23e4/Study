
#include <iostream>
#include "myStack.h"
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int choice;
	int found_value = 0;
	int bottom_range, top_range;
	Stack* myStk = new Stack; //выделение памяти для стека
	myStk->head = NULL;       //инициализация первого элемента	
	for (;;)
	{
		cout << "Выберите команду:" << endl;
		cout << "1 - Добавление элемента в стек" << endl;
		cout << "2 - Извлечение элемента из стека" << endl;
		cout << "3 - Вывод стека" << endl;
		cout << "4 - Очистить стек" << endl;
		cout << "5 - Сохранить в файл" << endl;
		cout << "6 - Считать из файла" << endl;
		cout << "7 - Подсчет количества повторяющихся элементов стека" << endl;
		cout << "8 - Есть ли в стеке значение из диапазона?" << endl;
		cout << "9 - Конец" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "Введите элемент: " << endl;
			cin >> choice;
			push(choice, myStk);
			break;
		case 2: choice = pop(myStk);
			if (choice != -1)
				cout << "Извлеченный элемент: " << choice << endl;
			break;
		case 3: cout << "Весь стек: " << endl;
			show(myStk);
			break;
		case 4: cout << "Стек очищен. " << endl;
			OCHISTKA(myStk);
			break;
		case 5: cout << "Стек сохранен в файл. " << endl;
			saveToFile(myStk);
			break;
		case 6: cout << "Результат считывания из файла: " << endl;
			loadFromFile(myStk);
			break;
		case 7: found_value = search_value(myStk);
			found_value ? printf("Количество повторяющихся элементов: %i\n", found_value) : printf("Повторяющихся значений нет или стек пуст.\n");
			break;
		case 8:cout << "Введите нижний предел диапазона:";
			cin >> bottom_range;
			cout << "\nВведите верхний предел диапазона:";
			cin >> top_range;
			found_value = search_value(bottom_range, top_range, myStk);
			found_value ? printf("В стеке содержится число из диапазона %i - %i.Первое подходящее значение: %i\n", bottom_range, top_range, found_value) : printf("Значений из данного диапазона в стеке нет\n");
			break;
		case 9: return 0;
			break;
		}
	}
	return 0;
}
