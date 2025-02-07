#pragma once
#define MAX 100
struct Stack
{
	int data;             //�������������� �������
	Stack* head;		 //������� ����� 
	Stack* next;		 //��������� �� ��������� �������
};

void show(Stack* myStk);         //��������
int pop(Stack* myStk);           //��������
void push(int x, Stack* myStk);  //���������
void OCHISTKA(Stack*& head);
void saveToFile(Stack* myStack);
void loadFromFile(Stack*& myStack);
int search_value(Stack* myStk);
int search_value(int bottom, int top, Stack* myStk);