#include "myStack.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	int choice;
	int bottom_range, top_range, found_value = 0;
	stack* myStack = new stack;
	myStack->head = NULL;
	for (;;)
	{
		cout << "Выберите команду:" << endl;
		cout << "1 - Добавление элемента в стек" << endl;
		cout << "2 - Извлечение элемента из стека" << endl;
		cout << "3 - Вывод стека" << endl;
		cout << "4 - Есть ли в стеке значение из диапазона?" << endl;
		cout << "5 - Выход" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: 
			cout << "Введите элемент:";
		    cin >> choice;
		    push(choice, myStack);
		break;
		case 2:
			choice = pop(myStack);
			choice != -1 ? cout << "Извлечённый элемент:" << choice << endl : cout << "Стек пуст" << endl;
		case 3: 
			cout << "Весь стек:" << endl;
			show(myStack);
			break;
		case 4: 
			cout << "Введите нижний предел диапазона:";
			cin >> bottom_range;
			cout << "\nВведите верхний предел диапазона:";
			cin >> top_range;
			found_value = search_value(bottom_range, top_range, myStack);
			found_value ? printf("В стеке содержится число из диапазона %i - %i.Первое подходящее значение: %i\n", bottom_range, top_range, found_value) : printf("Значений из данного диапазона в стеке нет\n");
			break;
		case 5:
			return 0;
			break;
		}
	}
	return 0;
}