
#include <iostream>
#include "myStack.h"
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	int choice;
	int found_value = 0;
	int bottom_range, top_range;
	Stack* myStk = new Stack; //��������� ������ ��� �����
	myStk->head = NULL;       //������������� ������� ��������	
	for (;;)
	{
		cout << "�������� �������:" << endl;
		cout << "1 - ���������� �������� � ����" << endl;
		cout << "2 - ���������� �������� �� �����" << endl;
		cout << "3 - ����� �����" << endl;
		cout << "4 - �������� ����" << endl;
		cout << "5 - ��������� � ����" << endl;
		cout << "6 - ������� �� �����" << endl;
		cout << "7 - ������� ���������� ������������� ��������� �����" << endl;
		cout << "8 - ���� �� � ����� �������� �� ���������?" << endl;
		cout << "9 - �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "������� �������: " << endl;
			cin >> choice;
			push(choice, myStk);
			break;
		case 2: choice = pop(myStk);
			if (choice != -1)
				cout << "����������� �������: " << choice << endl;
			break;
		case 3: cout << "���� ����: " << endl;
			show(myStk);
			break;
		case 4: cout << "���� ������. " << endl;
			OCHISTKA(myStk);
			break;
		case 5: cout << "���� �������� � ����. " << endl;
			saveToFile(myStk);
			break;
		case 6: cout << "��������� ���������� �� �����: " << endl;
			loadFromFile(myStk);
			break;
		case 7: found_value = search_value(myStk);
			found_value ? printf("���������� ������������� ���������: %i\n", found_value) : printf("������������� �������� ��� ��� ���� ����.\n");
			break;
		case 8:cout << "������� ������ ������ ���������:";
			cin >> bottom_range;
			cout << "\n������� ������� ������ ���������:";
			cin >> top_range;
			found_value = search_value(bottom_range, top_range, myStk);
			found_value ? printf("� ����� ���������� ����� �� ��������� %i - %i.������ ���������� ��������: %i\n", bottom_range, top_range, found_value) : printf("�������� �� ������� ��������� � ����� ���\n");
			break;
		case 9: return 0;
			break;
		}
	}
	return 0;
}
