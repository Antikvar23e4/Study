//������� ������� ��� ������� �����(������������� � �������������) �����.
//������� ��� �����, ������ � �������� ��������� �������.
//��� ����� ����� � ������� �������� ������ ������������� ��������.
//����� ����������� � ������������ ������� �������.
//������� ��� �������� ������� � ��������� �� ����������.

#include<iostream>
using namespace std;

struct node
{
    int elem;
    node* sled;
};
class Spisok {
private:
    node* no, * ko;
    int klad;
public:
    Spisok() { no = ko = NULL; }
    void POSTROENIE();
    void VYVOD();
    void DOBAVLENIE(int);
    int  Set_Udal() { return klad; }
    void YDALENIE();
    void OCHISTKA();
};

void main()
{
    setlocale(LC_ALL, "Rus");
    Spisok A;
    int el;

    A.POSTROENIE();
    A.VYVOD();
    cout << "������� ����������� �������: ";
    cin >> el;
    A.DOBAVLENIE(el); A.VYVOD();
    cout << "������ ������� �� �������.\n";
    A.YDALENIE(); A.VYVOD();
    el = A.Set_Udal();
    cout << "�������������� ���� ���������� �����: " << el << endl;
    A.OCHISTKA();

    cout << "\n";
    system("PAUSE");
}

void Spisok::POSTROENIE()
//���������� ������� �� ���� ����������������� ������
//��� ���������� �����.
//no - ��������� �� ������ �������.
//ko - ��������� �� ����� �������.
{
    node* r;
    int el;

    cout << "������� �������� �������:\n";
    cin >> el;
    if (el != 0)
    {
        r = new (node);
        (*r).elem = el; (*r).sled = NULL;
        no = r; ko = r; cin >> el;
        while (el != 0)
        {
            r = new (node);
            (*r).elem = el; (*r).sled = NULL;
            (*ko).sled = r; ko = r; cin >> el;
        }
    }
    else
    {
        r = NULL; no = r; ko = r;
    }
}

void Spisok::VYVOD()
//����� ����������� �������.
//no - ��������� �� ������ �������.
//ko - ��������� �� ����� �������.
{
    node* r;
    cout << "�������: "; r = no;
    while (r != NULL)
    {
        cout << (*r).elem << " "; r = (*r).sled;
    }
    cout << endl;
}

void Spisok::DOBAVLENIE(int el)
//���������� ����� � �������������� ����� el � �������,
//������������ �����������  no � ko.
{
    node* r;

    r = new (node);
    (*r).elem = el; (*r).sled = NULL;
    if (no != NULL)
    {
        (*ko).sled = r; ko = r;
    }
    else
    {
        no = r; ko = r;
    }
}

void Spisok::YDALENIE()
//�������� ����� �� �������, ������������ �����������
//no � ko, � ���������� ��� ��������������� ���� �
//�������� klad.
{
    node* q;

    if (no == NULL)
        cout << "������� ������, ��� ��� ������� �����!\n";
    else
    {
        klad = (*no).elem; q = no;
        no = (*no).sled; delete q;
    }
}

void Spisok::OCHISTKA()
//������� ���������� ������ � "����".
{
    node* q;

    q = no;
    if (no != NULL)
    {
        while (no != ko)
        {
            no = (*q).sled;
            delete q;  q = no;
        }
        delete no;
        no = ko = NULL;
    }
}


