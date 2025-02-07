#pragma once
#include <iostream>
#include <Windows.h>

struct Student
{
	char surname[15];		
	char name[10];			
	int year;				
	int course;				
	int group;				
	int OSMark;				
	int englishMark;		
	int boitMark;			
	int oapMark;			
	int chemistryMark;	
	Student* next;
};

struct Element
{
	Element* Prev;
	Element* Next;
	void* Data;
	Element(Element* prev, void* data, Element* next)
	{
		Prev = prev;
		Data = data;
		Next = next;
	}
};

struct Object
{
	Element* Head;
	Object()
	{
		Head = NULL;
	};

	bool Insert(void* data);
	void PrintList(void(*f)(void*));
	int CountList();
	int CountList(int);
	bool sortCourse();
	bool sortSurname();
	bool findAverage();
	bool findOldest();
	bool findYoungest();
	bool findBest();
	void insertAll();
};

Object Create();   

void print(void* b);
int menu();
void Example(Object*);
