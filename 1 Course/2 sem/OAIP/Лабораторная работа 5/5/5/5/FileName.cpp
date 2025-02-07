//������� ������, ���������� �������� ������ ����. ����� ����� ������������� ����������� ��������� ��� ������ ���������, ��� ����� ��������� ���. 
#include <iostream>
#include <fstream>
using namespace std;
struct list {
    int number;
    list* next;
};

void insert(list*&, float); //������� ���������� �������� 
float del(list*&, float);   //������� �������� 
int IsEmpty(list*);         //�������, ������� ���������, ���� �� ������
void printList(list*);      //������� ������
void menu(void);            //�������, ������������ ����
void sum(list*);            //������� �������� ����� ������������� ����������� ��������� 
void toFile(list*& p);         //������ � ����
void fromFile(list*& p);       //���������� �� �����

int main()
{
    setlocale(LC_CTYPE, "Russian");
    list* first = NULL; // ��������� 1 ������� ������
    int choice;
    int value;
    menu();    // ������� ���� 
    cout << " ? ";
    cin >> choice;
    while (choice != 7) {
        switch (choice)
        {
        case 1:
            cout << "������� ����� "; // �������� ����� � ������
            cin >> value;
            insert(first, value);
            menu();
            break;
        case 2:
            if (!IsEmpty(first)) { // ������� ����� �� ������
                cout << "������� ��������� ����� ";
                cin >> value;
                if (del(first, value)) {
                    cout << "������� ����� " << value << endl;
                    printList(first);
                }
                else {
                    cout << "����� �� �������" << endl;
                }
            }
            else {
                cout << "������ ����" << endl;
            }
            menu();
            break;
        case 3:   sum(first);  // ���������� �����  
            menu();
            break;
        case 4:
            printList(first);
            menu();
            break;
        case 5:    toFile(first);
            menu();
            break;
        case 6:    fromFile(first);
            menu();
            break;
        default:
            cout << "������������ �����" << endl;
            menu();
            break;
        }
        cout << "?  ";
        cin >> choice;
    }
    cout << "�����" << endl;
    return 0;
}

void menu(void)  //����� ���� 
{
    cout << "\n�������� �����:" << endl;
    cout << " 1 - ���� �����" << endl;
    cout << " 2 - �������� �����" << endl;
    cout << " 3 - ���������� ������ ������������� ����������� ���������" << endl;
    cout << " 4 - ����� ������ � ���������� ����" << endl;
    cout << " 5 - ������ ������ � ����" << endl;
    cout << " 6 - ����� ������ �� �����" << endl;
    cout << " 7 - �����" << endl;
}
//������� �� ������ �������
void insert(list*& p, float value) //���������� ����� value � ������ 
{
    list* newP = new list; // ������� ����� ������� ������
    if (newP != NULL)     //���� �� �����?  
    {
        newP->number = value; // � �������������� ���� �������� ��������
        newP->next = p; // � ���� ���������� �������� ���� ������� �������� ������� ��������
        p = newP;
    }
    else {
        cout << "�������� ���������� �� ���������" << endl;
    }
}

float del(list*& p, float value)  // �������� ����� 
{
    list* previous, * current, * temp;
    if (value == p->number)
    {
        temp = p;
        p = p->next;    // ����������� ���� 
        delete temp;      //���������� ������������� ���� 
        return value;
    }
    else
    {
        previous = p;
        current = p->next;
        while (current != NULL && current->number != value)
        {
            previous = current;
            current = current->next; // ������� � ���������� 
        }
        if (current != NULL)
        {
            temp = current;
            previous->next = current->next;
            free(temp);
            return value;
        }
    }
    return 0;
}

int IsEmpty(list* p) //������  ������? (1-��, 0-���) 
{
    return p == NULL;
}



void printList(list* p)  //����� ������ 
{
    if (p == NULL)
        cout << "������ ����" << endl;
    else
    {
        cout << "������:" << endl;
        while (p != NULL)
        {
            cout << "-->" << p->number;
            p = p->next;
        }
        cout << "-->NULL" << endl;
    }
}

void sum(list* p) { // ������� �����  ������������� ���������, ������� 5    
    int sm = 0;
    if (p == NULL)
        cout << "������ ����" << endl;
    else
    {
        while (p != NULL)
        {
            if (p->number > 9 && p->number < 100) {
                sm = sm + (p->number);
            }
            p = p->next;
        }
        if (sm != 0) {
            cout << "����� ������������� ����������� ��������� ����� " << sm << endl;
        }
        else {
            cout << "������������� ����������� ��������� ���" << endl;
        }
    }
}

void toFile(list*& p) {
    list* temp = p;
    list buf;
    ofstream frm("mList.dat");
    if (frm.fail())
    {
        cout << "\n ������ �������� �����";
        exit(1);
    }
    while (temp)
    {
        buf = *temp;
        frm.write((char*)&buf, sizeof(list));
        temp = temp->next;
    }
    frm.close();
    cout << "������ ������� � ���� mList.dat\n";
}

void fromFile(list*& p)          //���������� �� �����
{
    list buf, * first = nullptr;
    ifstream frm("mList.dat");
    if (frm.fail())
    {
        cout << "\n ������ �������� �����";
        exit(1);
    }
    frm.read((char*)&buf, sizeof(list));
    while (!frm.eof())
    {
        insert(first, buf.number);
        cout << "-->" << buf.number;
        frm.read((char*)&buf, sizeof(list));
    }
    cout << "-->NULL" << endl;
    frm.close();
    p = first;
    cout << "\n������ ������ �� ����� mList.dat\n";
}


