#include "myQueue.h"
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
        (*r).elem = el;
        (*r).sled = NULL;
        no = r; ko = r;
        cin >> el;
        while (el != 0)
        {
            if (el < 0) {
                r = new (node);
                (*r).elem = el;
                (*r).sled = NULL;
                (*ko).sled = r;
                ko = r;
            }
            cin >> el;
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

int Spisok::findMax() {
    if (no == NULL) { // ���� ������� �����
        return -1; // ������� ��� ������ ��� ��������� ����������
    }
    int max = no->elem; // �����������, ��� ������ ������� ������������
    node* curr = no->sled; // �������� �� ������� ��������
    while (curr != NULL) { // �������� �� ���� ��������� ���������
        if (curr->elem > max) { // ���� ������� ������� ������ �������������
            max = curr->elem; // ��������� ������������ �������
        }
        curr = curr->sled; // ��������� � ���������� ��������
    }
    return max;
}