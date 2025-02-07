#include "pch.h"
#include "Auxil.h"

namespace auxil
{
    void start()                          // �����  ���������� ��������� ����� �����
    {
        srand((unsigned)time(NULL));      // ��������� ���������� ��������� ����������
    };
    double dget(double rmin, double rmax) // �������� ��������� �����
    {
        return ((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin; // ������� ��������� ����� �� ������ ���������
    };
    int iget(int rmin, int rmax)         // �������� ��������� �����

    {
        return (int)dget((double)rmin, (double)rmax);
    };

    // ������� ��� ��������� ����� ���������
    int fibonacci(int n)
    {
        if (n <= 0)
            return 0;
        else if (n == 1)
            return 1;
        else
            return fibonacci(n - 1) + fibonacci(n - 2);
    }
}