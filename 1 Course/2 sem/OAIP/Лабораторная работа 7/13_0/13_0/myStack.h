#pragma once
#define MAX 100
struct Stack
{
	int data;             //информационный элемент
	Stack* head;		 //вершина стека 
	Stack* next;		 //указатель на следующий элемент
};

void show(Stack* myStk);         //прототип
int pop(Stack* myStk);           //прототип
void push(int x, Stack* myStk);  //прототипы
void OCHISTKA(Stack*& head);
void saveToFile(Stack* myStack);
void loadFromFile(Stack*& myStack);
int search_value(Stack* myStk);
int search_value(int bottom, int top, Stack* myStk);