#include "myStack.h"

int search_value(int bottom, int top, stack* myStack)
{
	stack* e = myStack->head;
	int a;
	if (e == NULL)
	{
		cout << "Стек пуст" << endl;
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
void push(int x, stack* myStack)
{
	stack* e = new stack;
	e->data = x;
	e->next = myStack->head;
	myStack->head = e;
}
void show(stack* myStack)
{
	stack* e = myStack->head;
	int a;
	if (e == NULL)
	{
		cout << "Стек пуст" << endl;
	}
	while (e != NULL)
	{
		a = e->data;
		cout << a << " ";
		e = e->next;
	}
	cout << endl;
}
int pop(stack* myStack)
{
	if (myStack->head == NULL)
	{
		cout << "Стек пуст" << endl;
		return -1;
	}
	else
	{
		stack* e = myStack->head;
		int a = myStack->head->data;
		myStack->head = myStack->head->next;
		delete e;
		return a;
	}
}

