#pragma once
#include <iostream>
using namespace std;

struct stack
{
	int data;
	stack* next;
	stack* head;
};

void show(stack* myStack);
int pop(stack* myStack);
void push(int x, stack* myStack);
int search_value(int bottom, int top, stack* myStack);