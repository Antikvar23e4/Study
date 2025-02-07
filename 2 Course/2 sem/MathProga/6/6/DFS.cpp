#include "stdafx.h" 
#include "DFS.h" 
#define NINF 0x80000000 // Определение константы для отрицательной бесконечности
#define INF  0x7fffffff // Определение константы для положительной бесконечности


void DFS::init(const graph::AList& al)
{
	this->al = &al; // Установка указателя на список смежности
	this->c = new Color[this->al->nV]; // Создание массива цветов вершин
	this->d = new int[this->al->nV]; // Создание массива времен открытия вершин
	this->f = new int[this->al->nV]; // Создание массива времен закрытия вершин
	this->p = new int[this->al->nV]; // Создание массива предшественников вершин
	this->t = 0; // Инициализация счетчика времени

	// Инициализация массивов
	for (int i = 0; i < this->al->nV; i++)
	{
		this->c[i] = WHITE; // Все вершины помечаются как не посещенные
		this->d[i] = this->f[i] = 0; // Времена открытия и закрытия вершин устанавливаются в 0
		this->p[i] = NIL; // Предшественники вершин устанавливаются в NIL
	}

	// Обход графа
	for (int i = 0; i < this->al->nV; i++)
		if (this->c[i] == WHITE) // Если вершина не посещена
		{
			this->visit(i); // Вызов метода visit для вершины i
			this->topological_sort.push_back(i); // Добавление вершины i в топологическую сортировку
		}
}

// Конструктор принимающий список смежности
DFS::DFS(const graph::AList& al)
{
	this->init(al); 
}

// Конструктор принимающий матрицу смежности
DFS::DFS(const graph::AMatrix& am)
{
	this->init(*(new graph::AList(am))); // Преобразование матрицы смежности в список смежности 
}

// Метод для посещения вершины в процессе обхода в глубину
void DFS::visit(int u)
{
	int v = NIL; // Инициализация переменной для соседней вершины
	this->c[u] = GRAY; // Пометка вершины как посещенной (серой)
	this->d[u] = ++(this->t); // Установка времени открытия вершины

	// Обход соседних вершин
	for (int j = 0; j < this->al->size(u); j++)
		if (this->c[v = this->al->get(u, j)] == WHITE) // Если соседняя вершина белая (не посещена)
		{
			this->p[v] = u; // Установка предшественника для вершины v
			this->visit(v); // Рекурсивный вызов метода для вершины v
			this->topological_sort.push_back(v); // Добавление вершины v в топологическую сортировку
		}

	this->c[u] = BLACK; // Пометка вершины как посещенной (черной)
	this->f[u] = ++(this->t); // Установка времени закрытия вершины
}

// Метод для получения значения времени закрытия вершины
int DFS::get(int i)
{
	int j = 0, min1 = INF, min2 = NINF, ntx = NIL;
	for (int j = 0; j <= i; j++)
	{
		for (int k = 0; k < this->al->nV; k++)
			if (this->f[k] < min1 && this->f[k] > min2)
			{
				min1 = this->f[k];
				ntx = k;
			}
		min2 = min1;  min1 = INF;
	}
	return ntx;
}
