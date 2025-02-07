#pragma once 

#include "Graph.h" 
#include <queue> 

//  (Breadth First Search) для поиска в ширину
struct BFS
{
	const static int INF = 0x7fffffff; // Константа для положительной бесконечности
	const static int NIL = -1; // Константа для представления отсутствия значения 
	enum Color { WHITE, GRAY, BLACK }; // Перечисление для цветов вершин
	const graph::AList* al; // Указатель на список смежности
	Color* c; // Массив для хранения цветов вершин
	int* d; // Массив для хранения расстояний до вершин
	int* p; // Массив для хранения предшественников вершин
	std::queue<int> q; // Очередь для обработки вершин
	//  пинимающий список смежности и стартовую вершину s
	BFS(const graph::AList& al, int s);
	//  принимающий матрицу смежности и стартовую вершину s
	BFS(const graph::AMatrix& am, int s);
	// Метод для инициализации данных перед обходом графа
	void init(const graph::AList& al, int s);
	// Метод для получения вершины из очереди для обработки
	int get();
};
