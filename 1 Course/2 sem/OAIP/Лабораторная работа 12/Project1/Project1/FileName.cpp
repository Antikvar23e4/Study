#include "Heap.h"
#include <iostream>
using namespace std;
heap::CMP cmpAAA(void* a1, void* a2)  //������� ���������
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
	heap::CMP
		rc = heap::EQUAL;
	if (A1->x > A2->x)
		rc = heap::GREAT;
	else
		if (A2->x > A1->x)
			rc = heap::LESS;
	return rc;
#undef A2
#undef A1 
}

int main()
{
	setlocale(LC_ALL, "rus");
	int k, choice;
	heap::Heap h1 = heap::create(100, cmpAAA);
	heap::Heap h2 = heap::create(100, cmpAAA);
	heap::Heap h3 = heap::create(100, cmpAAA);
	for (;;)
	{
		cout << "1 - ����� ���� 1 �� �����" << endl;
		cout << "2 - ����� ���� 2 �� �����" << endl;
		cout << "3 - �������� �������� � ���� 1" << endl;
		cout << "4 - �������� �������� � ���� 2" << endl;
		cout << "5 - ������� ������������ ������� � ���� 1" << endl;
		cout << "6 - ������� ����������� ������� � ���� 1" << endl;
		cout << "7 - ������� i-� ������� � ���� 1" << endl;
		cout << "8 - ���������� ������ � ������ ����" << endl;
		cout << "9 - ����� ���� 3 �� �����" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� �����" << endl;  cin >> choice;
		switch (choice)
		{
		case 0:  exit(0);
		case 1:  h1.scan(0);
			break;
		case 2:  h2.scan(0);
			break;
		case 3: {
			cout << "������������� ����� - ����� �����" << endl;
			do {
				AAA* a = new AAA;
				cout << "������� ����" << endl;
				cin >> k;
				if (k <= 0)break;
				a->x = k;
				h1.insert(a);
			} while (k >= 0);
		}
			  break;
		case 4: {
			cout << "������������� ����� - ����� �����" << endl;
			do {
				AAA* a = new AAA;
				cout << "������� ����" << endl;
				cin >> k;
				if (k <= 0)break;
				a->x = k;
				h2.insert(a);
			} while (k >= 0);
		}
			  break;
		case 5:   h1.extractMax();
			break;
		case 6:   h1.extractMin(); 
			break;
		case 7: int i; cout << "������� ����� ��������: ";
			cin >> i;
			cout << endl;
			h1.extractI(i);
			break;
		case 8:   h3.unionHeap(h1, h2);
			break;
		case 9:    h3.scan(0);
			break;
		default:  cout << endl << "������� �������� �������!" << endl;
		}
	} return 0;
}