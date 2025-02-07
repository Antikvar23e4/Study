
//���� �������� ������� �������� �� ������������� �������.
// ������ �� ���� ������� ��������������� �������������, ������� �����, ��������� ����� � ���������� �����������.
//� ���� �������� ���������� ����������.��� ������� �� ��� �� ����������� � ���� ������ ����������� ������(������������, �����, �������, ���������� ����) � ����������� �� ������ ������ ��������,
//  ��������� ������ � ����������� ���������� ���������� �� ������ � ���� �������.
//������ ���������� � ������ ����� ������ �������� �� ���� �����, � ����� ���������.
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

int _stateMenu;

void Menu() {
    cout << "�������� ��������:" << endl
        << "(1) ������ � ����������" << endl
        << "(2) ����������� ���������" << endl
        << "(3) ��������  ��������" << endl
        << "(4) �������� �� ���� ������" << endl
        << "(5) �������� � ������ ������ � ���� " << endl
        << "(6) ������ ����� " << endl
        << "(7) �������� ����������� � �����" << endl
        << "(8) ��������  �����" << endl
        << "��� �����: ";
    cin >> _stateMenu;
}


void infile();
void outfile();
void delitus();

int client_info;


char adress[20];
char phone[20];
char name[20];
char fio[20];
char kolvo[20];
char date[20];
char path[20];



int main()
{
    setlocale(LC_ALL, "rus");
    char client_info;

    Menu();
    while (_stateMenu != 0) {

        switch (_stateMenu)
        {
        case 1:
            system("cls");
            int vibor;
            system("cls");
            cout << "������ ������� 2 - �������, 1 - ������, 0 - �����������?" << endl;
            cin >> vibor;
            switch (vibor) {
            case 2:
                system("cls");
                cout << "������ �������!" << endl;
                system("pause");
                system("cls");
                Menu();
                break;
            case 1:
                system("cls");
                cout << "������� ������!" << endl;
                cout << "������������:" << endl;
                cin >> name;
                cout << "�����:" << endl;
                cin >> adress;
                cout << "�������:" << endl;
                cin >> phone;
                cout << "���������� ����:" << endl;
                cin >> fio;
                cout << "����������� ��������� �������: " << endl;
                cin >> kolvo;
                cout << "���� �������:" << endl;
                cin >> date;
                system("pause");
                system("cls");
                Menu();
                break;
            case 0:
                system("cls");
                cout << "������ ��������!" << endl;
                cout << "������������:" << name << endl;
                cout << "�����:" << adress << endl;
                cout << "�������:" << phone << endl;
                cout << "���������� ����:" << fio << endl;
                cout << "����������� ��������� �������: " << kolvo << endl;
                cout << "���� �������:" << date << endl;
                system("pause");
                system("cls");
                Menu();
                break;
            default:
                system("cls");
                cout << "������� ������ ����� ��������!" << endl;
                system("pause");
                system("cls");
                Menu();
            }
            break;
            system("pause");
            system("cls");
            Menu();
            break;
        case 2:
            system("cls");
            cout << "�������� ������� ��  ���� ������ ��� ����������� ���������: " << endl;
            cin >> client_info;
            cout << "�������� ���������!";
            cout << " ������ � ������������ ->" << endl;
            cout << "������������:" << name << endl;
            cout << "�����:" << adress << endl;
            cout << "�������:" << phone << endl;
            cout << "���������� ����:" << fio << endl;
            cout << "����������� ��������� �������: " << kolvo << endl;
            cout << "���� �������:" << date << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 3:
            system("cls");
            cout << "���������� � ����������" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 4:
            system("cls");
            cout << "�������� �� ���� ������!" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        default:
            system("cls");
            cout << "������� ������ ����� ��������!" << endl;
            system("pause");
            system("cls");
            Menu();
            break;
        case 5:
            system("cls");
            cout << "�������� � ������ ������ � ����, �������� �������� �������� � ����������" << endl;
            infile();
            system("pause");
            system("cls");
            Menu();
            break;
        case 6:
            system("cls");
            cout << "������ �����" << endl;
            outfile();
            system("pause");
            system("cls");
            Menu();
            break;
        case 7:
            system("cls");
            cout << "�������� ����������� � �����" << endl;
            delitus();
            system("pause");
            system("cls");
            Menu();
            break;
        case 8:
            system("cls");
            cout << "�������� �����" << endl;
            remove(path);
            system("pause");
            system("cls");
            Menu();
            break;

        }
    }
}

void infile() {
    cout << "Enter name" << endl;
    cin >> path;

    ofstream fout(path);//������� ������ ������ ofstream, ��������� ��� � ������ � ������ ����� ������������ ������
    if (!fout.is_open())// ���� ����  ������
    {
        cout << "�������� ����!";
    }
    else //��������� ������ � ��� ����
    {
        fout << "\n" << name;
        fout << "\n" << adress;
        fout << "\n" << phone;
        fout << "\n" << fio;
        fout << "\n" << kolvo;
        fout << "\n" << date;
        fout << "\n" << "-------------------------------------------" << endl;

    }

    fout.close();//�������� �����
}
void outfile() {
    char buff[50];
    ifstream fin(path); //������� ������ ������ ifstream � ������� ��� � ������, �� �������� ����� ������������� ����������
    do { //��������� �����
        fin.getline(buff, 50);
        cout << buff << endl;
        buff[0] = 0;
    } while (!fin.eof());// ���� �� ����� �����

}

void delitus() {
    ofstream fin(path, ios_base::out | ios_base::trunc); //��������� ��� 1.������� ���� ��� ������ 2.������� ���������� �����, ���� �� ����������
    fin.close();//�������� �����

}