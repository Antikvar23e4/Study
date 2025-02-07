#include "List.h"
#include <iostream>
#include <string.h>
using namespace std;

bool Object::Insert(void* data)
{
	if (Head == NULL)
	{
		Head = new Element(NULL, data, Head);
	}
	else
	{
		Head = (Head->Prev = new Element(NULL, data, Head));
	}
	return 1;
}

void Object::PrintList(void(*f)(void*))
{
	Element* e = Head;
	while (e != NULL)
	{
		f(e->Data);
		e = e->Next;
	};
}

int Object::CountList()
{
	Element* e = Head;
	int i = 0;
	while (e != NULL)
	{
		i++;
		e = e->Next;
	}
	return i;
}

Object Create()
{
	return *(new Object());
}

bool Object::sortCourse()
{
	int size = CountList();
	Element* e = Head;
	void* tempData;

	for (int i = 0; i < size - 1; i++) {

		Element* e = Head;

		for (int j = 0; j < size - i - 1; j++) {

			void* b1 = e->Data;
			Student* a1 = (Student*)b1;
			int c1 = a1->course;

			void* b2 = e->Next->Data;
			Student* a2 = (Student*)b2;
			int c2 = a2->course;

			if (c1 > c2) {
				tempData = e->Data;
				e->Data = e->Next->Data;
				e->Next->Data = tempData;
			}

			e = e->Next;

		}
	}
	return 1;
}

bool Object::sortSurname()
{
	int size = CountList();
	Element* e = Head;
	void* tempData;

	for (int i = 0; i < 3; i++)
	{
		int courseSize = CountList(i + 1);

		for (int j = 0; j < courseSize - 1; j++) {

			Element* e = Head;

			if (i == 1)
			{
				for (int l = 0; l < courseSize; l++)
				{
					e = e->Next;
				}
			}

			if (i == 2)
			{
				for (int l = 0; l < size - courseSize; l++)
				{
					e = e->Next;
				}
			}

			for (int k = 0; k < courseSize - j - 1; k++) {

				void* b1 = e->Data;
				Student* a1 = (Student*)b1;
				char* c1 = a1->surname;

				void* b2 = e->Next->Data;
				Student* a2 = (Student*)b2;
				char* c2 = a2->surname;

				if (strcmp(c1, c2) > 0) {
					tempData = e->Data;
					e->Data = e->Next->Data;
					e->Next->Data = tempData;
				}

				e = e->Next;

			}
		}
	}
	return 1;
}

bool Object::findAverage()
{
	int size = CountList();
	Element* e = Head;

	float math = 0, pe = 0, history = 0, oap = 0, chemistry = 0;
	int num = 0, courses = 0, groups = 0;

	for (courses = 0; courses < 3; courses++)
	{
		for (groups = 0; groups < 2; groups++)
		{
			math = 0;
			pe = 0;
			history = 0;
			oap = 0;
			chemistry = 0;
			num = 0;

			Element* e = Head;

			for (int k = 0; k < size; k++)
			{
				void* b1 = e->Data;
				Student* a1 = (Student*)b1;
				int c1 = a1->course;
				int d1 = a1->group;

				if (c1 == courses + 1 && d1 == groups + 1)
				{
					math += a1->OSMark;
					pe += a1->englishMark;
					history += a1->boitMark;
					oap += a1->oapMark;
					chemistry += a1->chemistryMark;
					num++;
				}
				e = e->Next;
			}
			math = math / num;
			pe = pe / num;
			history = history / num;
			oap = oap / num;
			chemistry = chemistry / num;
			cout << "Ñðåäíèé áàëë " << courses + 1 << " êóðñà " << groups + 1 << " ãðóïïû: ";
			cout << "ìàòåìàòèêà - " << math << ", ôèçêóëüòóðà - " << pe << ", èñòîðèÿ - " << history << ", ÎÀÏ - " << oap << ", õèìèÿ - " << chemistry << ".";
			cout << endl;
		}
	}
	return 1;
}

bool Object::findOldest()
{
	int size = CountList();
	Element* e = Head;
	int oldest = 2020;
	Student* st = NULL;

	for (int i = 0; i < size; i++)
	{
		void* b1 = e->Data;
		Student* a1 = (Student*)b1;
		int c1 = a1->year;

		if (c1 < oldest)
		{
			oldest = c1;
			st = a1;
		}
		e = e->Next;
	}
	cout << "Ñàìûì ñòàðøèì ñòóäåíòîì " << oldest << " ãîäà ðîæäåíèÿ ÿâëÿåòñÿ ";
	print(st);

	return 1;
}

bool Object::findYoungest()
{
	int size = CountList();
	Element* e = Head;
	int youngest = 1920;
	Student* st = NULL;

	for (int i = 0; i < size; i++)
	{
		void* b1 = e->Data;
		Student* a1 = (Student*)b1;
		int c1 = a1->year;

		if (c1 > youngest)
		{
			youngest = c1;
			st = a1;
		}
		e = e->Next;
	}
	cout << "Ñàìûì ìëàäøèì ñòóäåíòîì " << youngest << " ãîäà ðîæäåíèÿ ÿâëÿåòñÿ ";
	print(st);

	return 1;
}

bool Object::findBest()
{
	int size = CountList();
	Element* e = Head;
	int best = 0;
	Student* st = NULL;

	for (int i = 0; i < size; i++)
	{
		void* b1 = e->Data;
		Student* a1 = (Student*)b1;
		int c1 = a1->OSMark + a1->englishMark + a1->boitMark + a1->oapMark + a1->chemistryMark;

		if (c1 > best)
		{
			best = c1;
			st = a1;
		}
		e = e->Next;
	}
	cout << "Ñàìûì ëó÷øèì ñòóäåíòîì ñ òî÷êè çðåíèÿ óñïåâàåìîñòè ÿâëÿåòñÿ ";
	print(st);

	return true;
}

int Object::CountList(int x)
{
	Element* e = Head;
	int i = 0;

	void* b = e->Data;
	Student* a = (Student*)b;
	int y = a->course;

	while (e != NULL)
	{
		void* b = e->Data;
		Student* a = (Student*)b;
		int y = a->course;

		if (x == y)
			i++;
		e = e->Next;
	}
	return i;
}

void print(void* b)       
{
	Student* a = (Student*)b;
	cout << a->surname;
	cout << " " << a->name << endl;
	cout << "Ãîä ðîæäåíèÿ: " << a->year << endl;
	cout << "Êóðñ: " << a->course << endl;
	cout << "Ãðóïïà: " << a->group << endl;
	cout << "Îöåíêà ïî ÎÑ: " << a->OSMark << endl;
	cout << "Îöåíêà ïî àíãëèéñêîìó: " << a->englishMark << endl;
	cout << "Îöåíêà ïî ÎÈÒ: " << a->boitMark << endl;
	cout << "Îöåíêà ïî ÎÀÏ: " << a->oapMark << endl;
	cout << "Îöåíêà ïî õèìèè: " << a->chemistryMark << endl << endl;
}