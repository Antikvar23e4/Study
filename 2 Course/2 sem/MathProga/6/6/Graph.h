#pragma once 

#include <list> 
#include "Graph.h" 

namespace graph 
{
    struct AList; 
    struct AMatrix  
    {
        int nV;                 // ���������� ������
        int* mr;                // ��������� �� ������, �������� ������������� �������
        AMatrix(int n, int mr[]);
        AMatrix(const AList& al);
        void set(int i, int j, int r);
        int  get(int i, int j)const;
    };

    struct AList
    {
        int nV;                 // ���������� ������
        std::list<int>* mr;     // ��������� �� ������ �������, �������������� ������ ���������
        // �������� ������ ��������� � �������� ����������� ������
        void create(int n);
        // ���������� ������ � ������, �������������� ������ ���������
        AList(int n, int mr[]);
        // �����������, ����������� ������� ��������� � ������������� �� � ������ ���������
        AList(const AMatrix& am);
        // ����� ��� ���������� ����� ����� ��������� i � j
        void add(int i, int j);
        // ����� ��� ��������� ������� ������ �� ������� i
        int  size(int i) const;
        // ����� ��� ��������� �������� � ������� (i, j) � ������ ���������
        int  get(int i, int j)const;
    };

}; 
