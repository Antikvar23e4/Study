//�������. ���� �������� ������� � ������������: �������� ������ �������, ������������ ������, ���-������ ���������; 
//�����, �������� ��� �����, ���� �����, ���� ��������. ����� ������� �� ������������.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define SIZE 2

void vvod();
void vivod();
void poisk();

union Lombard {
    char fio[4];
    char tovar[10];
    int sum;
    int zalog;
    char date[5];
    char hranenie[5];
} user[SIZE];

int main() {
    setlocale(LC_CTYPE, "rus");
    int vibor;
    int lets = 1;
    while (lets == 1) {
        cout << "(1) - ���� � ����������\n"
            << "(2) - ����� �� �����\n"
            << "(3) - ����� �� ������������\n";
        cin >> vibor;

        switch (vibor) {
        case 1:
            system("cls");
            vvod();
            system("pause");
            system("cls");
            cout << "������� 1 ��� ����������� ";
            cin >> lets;
            break;
        case 2:
            system("cls");
            vivod();
            system("pause");
            system("cls");
            cout << "������� 1 ��� ����������� ";
            cin >> lets;
            break;
        case 3:
            system("cls");
            poisk();
            system("pause");
            system("cls");
            cout << "������� 1 ��� ����������� ";
            cin >> lets;
            break;
        }
    }
}

void vvod() {
    int enter, enter1;
    ofstream out("myfile.txt"); // �������� ���� ��� ������
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "����� ����� " << i + 1;
            cout << "\n������� ��� "; cin >> user[i].fio;
            out << user[i].fio << endl;
            cout << "\n������� ������������ ������ "; cin >> user[i].tovar;
            out << user[i].tovar << endl;
            cout << "\n������� ��������� ��������� "; cin >> user[i].sum;
            out << user[i].sum << endl;
            cout << "\n������� �����, �������� ��� ����� "; cin >> user[i].zalog;
            out << user[i].zalog << endl;
            cout << "\n������� ���� ����� "; cin >> user[i].date;
            out << user[i].date << endl;
            cout << "\n������� ���� �������� "; cin >> user[i].hranenie;
            out << user[i].hranenie << endl;
            cout << "������ � ���� ���������" << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    out.close();
}

void vivod() {
    ifstream in("myfile.txt"); // �������� ���� ��� ������
    string strInput;
    if (in.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "����� ����� " << i + 1;
            cout << "\n��� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n������������ ������ ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n��������� ��������� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n�����, �������� ��� ����� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n���� ����� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n���� �������� ";
            in >> strInput;
            cout << strInput << endl;
            cout << endl << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    in.close();
}

void poisk() {
    float f = false;
    char poisk[4];
    char* poisk2 = new char[4];
    string strInput;
    ifstream in("myfile.txt");
    cout << "������� ��� ��� ������ "; cin >> poisk;
    if (in.is_open()) {
        while (in.good()) {
            in >> poisk2;
            if (strcmp(poisk2, poisk) == 0) {
                f = true;
                cout << "\n��� " << poisk2 << endl;
                cout << "\n������������ ������ ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n��������� ��������� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n�����, �������� ��� ����� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n���� ����� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n���� �������� ";
                in >> strInput;
                cout << strInput << endl;
                cout << endl << endl;
            }
        }
        if (f == false) {
            cout << "�� �������" << endl;
        }
    }
}
