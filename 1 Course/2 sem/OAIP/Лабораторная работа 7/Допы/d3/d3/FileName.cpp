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
		cout << "�������� �������:" << endl;
		cout << "1 - ���������� �������� � ����" << endl;
		cout << "2 - ���������� �������� �� �����" << endl;
		cout << "3 - ����� �����" << endl;
		cout << "4 - ���� �� � ����� �������� �� ���������?" << endl;
		cout << "5 - �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: 
			cout << "������� �������:";
		    cin >> choice;
		    push(choice, myStack);
		break;
		case 2:
			choice = pop(myStack);
			choice != -1 ? cout << "����������� �������:" << choice << endl : cout << "���� ����" << endl;
		case 3: 
			cout << "���� ����:" << endl;
			show(myStack);
			break;
		case 4: 
			cout << "������� ������ ������ ���������:";
			cin >> bottom_range;
			cout << "\n������� ������� ������ ���������:";
			cin >> top_range;
			found_value = search_value(bottom_range, top_range, myStack);
			found_value ? printf("� ����� ���������� ����� �� ��������� %i - %i.������ ���������� ��������: %i\n", bottom_range, top_range, found_value) : printf("�������� �� ������� ��������� � ����� ���\n");
			break;
		case 5:
			return 0;
			break;
		}
	}
	return 0;
}