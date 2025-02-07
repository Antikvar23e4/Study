#pragma once 
#include <iostream>

struct Element {                  // Ёлемент списка 
	Element* Prev;                // указатель на предыдущий элемент 
	Element* Next;                // указатель на следующий элемент 
	void* Data;                  //  данные  
	Element(Element* prev, void* data, Element* next) { // конструктор
		Prev = prev;
		Data = data;
		Next = next;
	}
	Element* GetNext() {           // получить следующий
		return Next;
	};
	Element* GetPrev() {          // получить предыдущий  
		return Prev;
	};
};

//-----------------------------------------------------------
struct Object {                    // Ѕлок управлени€ списком 
	Element* Head;                 // указатель на начало списка
	Object() {
		Head = NULL;
	};
	Element* GetFirst() {           // получить первый элемент списка
		return Head;
	};
	Element* GetLast();            // получить последний элемент списка
	Element* Search(void* data);   // найти  первый элемент по данным 
	bool Insert(void* data);       // добавить элемент в начало
	bool Delete(Element* e);       // удалить по адресу элемента 
	bool Delete(void* data);       // удалить первый по данным
	void PrintList(void(*f)(void*));
	void PrintList(void(*f)(void*), Element*);
	void CountList(void(*f)(void*));
	void DeleteList();
};
Object Create();                   // создать список


