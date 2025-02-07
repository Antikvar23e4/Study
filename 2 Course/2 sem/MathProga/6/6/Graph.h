#pragma once 

#include <list> 
#include "Graph.h" 

namespace graph 
{
    struct AList; 
    struct AMatrix  
    {
        int nV;                 // Количество вершин
        int* mr;                // Указатель на массив, хранящий представление матрицы
        AMatrix(int n, int mr[]);
        AMatrix(const AList& al);
        void set(int i, int j, int r);
        int  get(int i, int j)const;
    };

    struct AList
    {
        int nV;                 // Количество вершин
        std::list<int>* mr;     // Указатель на массив списков, представляющий список смежности
        // создания списка смежности с заданным количеством вершин
        void create(int n);
        // количество вершин и массив, представляющий список смежности
        AList(int n, int mr[]);
        // Конструктор, принимающий матрицу смежности и преобразующий ее в список смежности
        AList(const AMatrix& am);
        // Метод для добавления ребра между вершинами i и j
        void add(int i, int j);
        // Метод для получения размера списка на вершине i
        int  size(int i) const;
        // Метод для получения значения в позиции (i, j) в списке смежности
        int  get(int i, int j)const;
    };

}; 
