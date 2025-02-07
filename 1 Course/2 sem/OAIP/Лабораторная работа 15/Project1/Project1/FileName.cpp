#include "Hash.h"
#include <iostream>

int MultiplicativeHashFunction(int key, int size)
{
	double A = (sqrt(5) - 1) / 2; // Константа A: (sqrt(5) - 1) / 2
	return static_cast<int>(size * (key * A - static_cast<int>(key * A)));
}

int HashFunction(int key, int size, int p)    //Хеш-функция
{
	return (MultiplicativeHashFunction(key, size) + p) % size;
}
//-------------------------------
int Next_hash(int hash, int size, int p)
{
	return (hash + 5 * p + 3 * p * p) % size;
}
//-------------------------------
Object create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));
}
//-------------------------------
Object::Object(int size, int(*getkey)(void*))
{
	N = 0;
	this->size = size;
	this->getKey = getkey;
	this->data = new void* [size];
	for (int i = 0; i < size; ++i)
		data[i] = NULL;
}
//-------------------------------
bool Object::insert(void* d)
{
	bool b = false;
	if (N != size)
		for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0);
			i != size && !b;  j = Next_hash(j, size, ++i))
			if (data[j] == NULL || data[j] == DEL)
			{
				data[j] = d;
				N++;
				b = true;
			}
	return b;
}
//-------------------------------
int Object::searchInd(int key)
{
	int t = -1;
	bool b = false;
	if (N != 0)
		for (int i = 0, j = HashFunction(key, size, 0); data[j] != NULL && i != size && !b; j = HashFunction(key, size, ++i))
			if (data[j] != DEL)
				if (getKey(data[j]) == key)
				{
					t = j; b = true;
				}
	return t;
}
//-------------------------------
void* Object::search(int key)
{
	int t = searchInd(key);
	return(t >= 0) ? (data[t]) : (NULL);
}
//-------------------------------
void* Object::deleteByKey(int key)
{
	int i = searchInd(key);
	void* t = data[i];
	if (t != NULL)
	{
		data[i] = DEL;
		N--;
	}
	return t;
}
//-------------------------------
bool Object::deleteByValue(void* d)
{
	return(deleteByKey(getKey(d)) != NULL);
}
//-------------------------------
void Object::scan(void(*f)(void*))
{
	for (int i = 0; i < this->size; i++)
	{
		std::cout << " Элемент" << i;
		if ((this->data)[i] == NULL)
			std::cout << "  пусто" << std::endl;
		else
			if ((this->data)[i] == DEL)
				std::cout << "  удален" << std::endl;
			else
				f((this->data)[i]);
	}
}

void Object::CompareCollisions(Object& H, int key, void* data)
{
	int p = 0;
	int linearCollisions = 0;
	int quadraticCollisions = 0;

	while (true)
	{
		int linearIndex = HashFunction(key, H.size, p);
		int quadraticIndex = Next_hash(HashFunction(key, H.size, 0), H.size, p);

		if (H.data[linearIndex] == NULL || H.data[linearIndex] == DEL)
		{
			H.data[linearIndex] = data;
			break;
		}
		else
		{
			linearCollisions++;
		}

		if (H.data[quadraticIndex] == NULL ||  H.data[quadraticIndex] == DEL)
		{
			H.data[quadraticIndex] = data;
			break;
		}
		else
		{
			quadraticCollisions++;
		}

		p++;
	}

	std::cout << "Колизии: " << linearCollisions << std::endl;
}