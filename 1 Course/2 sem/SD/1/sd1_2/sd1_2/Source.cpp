//�������� ���������, � ������� ����� ������� ��� �������� ������������ ������ � �������� n �����, � ������� �� �����.


#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    int x,i;
    forward_list<int> newlist = { 3, 2, 8, 4, 1 };
    newlist.clear();//������� ��� ��������
    cout << "������� ������� ����� ������ ��������: " << endl;
    cin >> x;
    for (int i = 0; i < x; i++) {
        newlist.emplace_front(rand() % 10);//��������� ������� � ������ ������
    }
    for (int n : newlist)//����� ������ ������
    {
        cout << n << "\t";
    }
}
