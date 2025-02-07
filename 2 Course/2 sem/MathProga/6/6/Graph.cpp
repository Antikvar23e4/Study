#include "stdafx.h" 
#include "Graph.h"

namespace graph 
{

	AMatrix::AMatrix(int n, int mr[])
	{
		this->nV = n; // Установка количества вершин
		this->mr = mr; // Установка указателя на массив, представляющий матрицу
	};

	AMatrix::AMatrix(const AList& al)
	{
		this->nV = al.nV; // Установка количества вершин
		this->mr = new int[this->nV * this->nV]; // Выделение памяти под массив, представляющий матрицу

		// Инициализация матрицы нулями
		for (int k = 0; k < this->nV * this->nV; k++)
			mr[k] = 0;

		// Заполнение матрицы значениями из списка смежности
		for (int i = 0; i < this->nV; i++)
			for (int j = 0; j < al.size(i); j++)
				this->set(i, al.get(i, j), 1); // Установка единицы в соответствующей ячейке матрицы
	};

	//установки значения в матрице по заданным координатам
	void AMatrix::set(int i, int j, int r)
	{
		this->mr[i * this->nV + j] = r;
	};

	// получения значения из матрицы по заданным координатам
	int  AMatrix::get(int i, int j)const
	{
		return this->mr[i * this->nV + j];
	};

	//создания списка смежности с заданным размером
	void AList::create(int n)
	{
		this->mr = new std::list<int>[this->nV = n];
	};

	//  матрицу смежности и преобразующий ее в список смежности
	AList::AList(const AMatrix& am)
	{
		this->create(am.nV); // Создание списка смежности с количеством вершин, равным количеству вершин в матрице

		// Заполнение списка смежности на основе матрицы смежности
		for (int i = 0; i < this->nV; i++)
			for (int j = 0; j < this->nV; j++)
				if (am.get(i, j) != 0)
					this->add(i, j); // Добавление ребра между вершинами
	};

	// Конструктор, принимающий количество вершин и массив, представляющий список смежности
	AList::AList(int n, int mr[])
	{
		this->create(n); // Создание списка смежности с заданным количеством вершин

		// Заполнение списка смежности на основе предоставленного массива
		for (int i = 0; i < this->nV; i++)
			for (int j = 0; j < this->nV; j++)
				if (mr[i * this->nV + j] != 0)
					this->add(i, j); // Добавление ребра между вершинами
	};

	// Метод для добавления ребра между вершинами в списке смежности
	void AList::add(int i, int j)
	{
		this->mr[i].push_back(j);
	};

	// Метод для получения размера списка, связанного с вершиной i
	int  AList::size(int i) const
	{
		return (int)this->mr[i].size();
	};

	// Метод для получения значения в списке смежности по заданным координатам
	int  AList::get(int i, int j)const
	{
		std::list<int>::iterator rc = this->mr[i].begin();
		for (int k = 0; k < j; k++)
			rc++;
		return (int)*rc;
	};
}; 
