//����������� ������� ����� � ����������, ������ �� ����� � ������. 
//���������� �����������.������ ����������, ����, ��������� �����, ���� �������, ��� ������ (�����, ��������� � �.��.), 
//���� ���������� ����������, ��������. ����� ������������ ������� �� ���������.

#include <iostream>
#include <fstream>
#define SIZE 1
using namespace std;

union automobile
{
    char brand[16];
    char owner[16];
    char color[8];
    int number;
    int date;
    int techno;
    char type[16];
};

automobile users[SIZE];

void input();
void output();
void find();

int main() {
    setlocale(LC_CTYPE, "rus");
    system("chcp 1251");
    system("cls");
    int choice;
    int lets = 1;
    while (lets == 1) {
        cout << "(1) - ���� ����������\n"
            << "(2) - ����� �� �����\n"
            << "(3) - ����� �� ���������\n"
            << "(4) - ����� �� ���������\n" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            input();
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            output();
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            find();
            system("pause");
            system("cls");
            break;
        case 4: lets = 0; break;
        }
    }
}

void input() {
    int enter, buffer;
    ofstream out;          // ����� ��� ������
    out.open("myfile.txt"); // �������� ���� ��� ������
    if (out.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "\n������� ��������� "; cin >> users[i].owner;
            out << users[i].owner << endl;
            cout << "\n������� ����� ���������� "; cin >> users[i].brand;
            out << users[i].brand << endl;
            cout << "\n������� ���� ���������� "; cin >> users[i].color;
            out << users[i].color << endl;
            cout << "\n������� ��������� ����� "; cin >> users[i].number;
            out << users[i].number << endl;
            cout << "\n������� ���� ������� "; cin >> users[i].date;
            out << users[i].date << endl;
            cout << "\n������� ��� ������ "; cin >> users[i].type;
            out << users[i].type << endl;
        }
    }
    else {
        cout << "Error!" << endl;
    }
    out.close();
}

void output() {
    ifstream in("myfile.txt"); // �������� ���� ��� ������
    string strInput;
    if (in.is_open()) {
        for (int i = 0; i < SIZE; i++) {
            cout << "���� ����� " << i + 1;
            cout << "\n�������� ";
            in >> strInput;
            cout << strInput << endl;;
            cout << "\n����� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n���� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n��������� ����� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n���� ������� ";
            in >> strInput;
            cout << strInput << endl;
            cout << "\n��� ������ ";
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

void find() {
    float f = false;
    char find[8];
    char* find2 = new char[8];
    string strInput;
    ifstream in("myfile.txt");
    cout << "������� ��������� ��� ������ "; cin >> find;
    if (in.is_open()) {
        while (in.good()) {
            in >> find2;
            if (strcmp(find2, find) == 0) {
                f = true;
                cout << "\n�������� ";
                cout << find2 << endl;;
                cout << "\n����� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n���� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n��������� ����� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n���� ������� ";
                in >> strInput;
                cout << strInput << endl;
                cout << "\n��� ������ ";
                in >> strInput;
                cout << strInput << endl;
            }
        }
        if (f == false) {
            cout << "�� �������" << endl;
        }
    }
}