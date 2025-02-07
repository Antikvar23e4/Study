#include <fstream>
#include <iostream>
#include "myStack.h"
using namespace std;

void push(int x, Stack* myStk)   //���������� �������� � � ����	
{
	Stack* e = new Stack;    //��������� ������ ��� ������ ��������
	e->data = x;             //������ �������� x � ���� v 
	e->next = myStk->head;   //������� ������� �� ��������� ������� 
	myStk->head = e;         //����� ������� �� ������� ������
}
int pop(Stack* myStk)   //���������� (��������) �������� �� �����
{
	if (myStk->head == NULL)
	{
		cout << "���� ����!" << endl;
		return -1;               //���� ���� ���� - ������� -1 
	}
	else
	{
		Stack* e = myStk->head;   //� - ���������� ��� �������� ������ ��������
		int a = myStk->head->data;   //������ ����� �� ���� data � ���������� a 
		myStk->head = myStk->head->next; //������� �������
		delete e;                        //�������� ��������� ����������
		return a;                        //������� �������� ���������� ��������
	}
}
void show(Stack* myStk)    //����� �����
{
	Stack* e = myStk->head;    //����������� ��������� �� ������� �����
	int a;
	if (e == NULL)
		cout << "���� ����!" << endl;
	while (e != NULL)
	{
		a = e->data;          //������ �������� � ���������� a 
		cout << a << " ";
		e = e->next;
	}
	cout << endl;
}
void OCHISTKA(Stack*& head)
//������� ���������� ������ � "����".
{
	Stack* temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void saveToFile(Stack* myStack) {
	ofstream file("Hello.txt");
	if (file.is_open()) {
		while (myStack) {
			file << myStack->data << endl;
			myStack = myStack->next;
		}
		file.close();
	}
}

void loadFromFile(Stack*& myStack) {
	ifstream file("Hello.txt");
	if (file.is_open()) {
		int data;
		while (file >> data) {
			Stack* node = new Stack;
			node->data = data;
			node->next = myStack;
			myStack = node;
		}
		file.close();
	}
}

int search_value(Stack* myStk)
{
	Stack* e = myStk->head;
	int* exception = new int[MAX];
	*(exception + 0) = 0;
	int a, l, repeated = 0, k = 0, coming = 0, check = 0, F = 0, once = 0;
	if (e == NULL)
	{
		cout << "���� ����" << endl;
		return 0;
	}
	while (e != NULL)
	{
		F = 0;
		check = 0;
		a = e->data;
		e = myStk->head;
		for (; e != NULL; )
		{
			if (e == NULL)
			{
				break;
			}
			l = e->data;
			for (int i = 0; i <= k; i++)
			{
				if (*(exception + i) == a)
				{
					goto part1;
				}
			}
			if (a == l && once != F)
			{
				check++;
				*(exception + (k++)) = a;
			}
		part1:
			e = e->next;
			F++;
		}
		if (check == 1)
		{
			repeated++;
		}
		coming++;
		e = myStk->head;
		once = 0;
		for (int i = 0; i < coming; i++)
		{
			e = e->next;
			once++;
		}
	}
	delete[] exception;
	return repeated;
}

int search_value(int bottom, int top, Stack* myStk)
{
	Stack* e = myStk->head;
	int a;
	if (e == NULL)
	{
		cout << "���� ����" << endl;
		return 0;
	}
	while (e != NULL)
	{
		a = e->data;
		if (a > bottom && a < top)
		{
			return a;
		}
		e = e->next;
	}
	return 0;
}