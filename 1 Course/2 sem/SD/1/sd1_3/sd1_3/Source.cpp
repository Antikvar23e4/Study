//�������� ���������, � ������� � ������ ����������� ������ ����������� n ��������� � ������� �� �����.

#include <iostream> 
#include <list>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    int x, i;
    list<int> newlist = { 6, 2, 8, 4, 5 };
    cout << "�������������� ������: : " << endl;
    for (int n : newlist)
    {
        cout << n << "\t";
    }
    cout << "" << endl;
    cout << "������� ������� ����� ������ ��������: " << endl;
    cin >> x;
    for (int i = 0; i < x; i++) {
        newlist.push_front(rand() % 10);//��������� ������� � ������ ������
    }

    cout << "�������� ������: : " << endl;
    for (int n : newlist)
    {
        cout << n << "\t";
    }
}
