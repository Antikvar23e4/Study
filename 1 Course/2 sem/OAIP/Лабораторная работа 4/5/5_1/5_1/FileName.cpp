//����������� �� ����� FILE1 � ���� FILE2 ������, ������� � ��������� �� �������. ���������� ��-�������� �������� � ��������� ����� FILE2.
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");

    int n = 4;
    char str[25];
    int pos = 0;

    ifstream in("in.txt"); // read
    ofstream out("out.txt"); // write

    char ch;
    // �������� �� ����� � ����������� 4 �������
    while (in.good() && n)
    {
        ch = in.get();
        if (ch == '\n')
            n--;
    }

    cout << "\n� ���� �����������: " << endl;
    while (in.good() && !in.eof())
    {
        ch = in.get();
        if (ch == '\n') {
            cout << endl;
            pos = 0;
        }
        if (ch == ' ')
        {
            pos = 0;
        }
        pos++;
        cout << ch;
        out << ch;
    }
    pos -= 2;
    cout << "\n���������� �������� � ��������� �������  �����: " << pos << endl;
}