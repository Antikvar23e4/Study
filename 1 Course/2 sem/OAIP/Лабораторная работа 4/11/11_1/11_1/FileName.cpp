//����������� �� ����� FILE1 � ���� FILE2 ��� ������, ������� �������� ������ ���� �����. ����� ����� �������� ����� �  ����� FILE2.
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

string get_word(istream& is) {
    string w;
    is >> w;
    return w;
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    string line;
    cout << "���������� ������� �����: " << endl;
    ifstream FILE("FILE1.txt"); // �������� ���� ��� ������
    if (FILE.is_open())
    {
        while (getline(FILE, line))
        {
            cout << line << endl;
        }
    }
    FILE.close();     // ��������� ����

    ofstream FILE2("FILE2.txt");
    ifstream FILE1("FILE1.txt");
    int count = 0;
    cout << "���������� ������� �����:" << endl;
    while (getline(FILE1, line)) {

        if (count >= 0 && count < 5) {

            if (line.find(' ') != string::npos)
            {
            }
            else {
                FILE2 << line << endl;
                cout << line << endl;
            }
        }
    }
    FILE2.close();
    FILE1.close();
    string word, max_word, min_word;
    size_t len, max_len = 0, min_len = 1000;
    ifstream file("FILE2.txt");

    while (file) {
        word = get_word(file);
        if (word.length() == 0)
            break;
        len = word.length();
        if (len > max_len) {
            max_len = len;
            max_word = word;
        }
        if (len < min_len) {
            min_len = len;
            min_word = word;
        }
    }

    file.close();

    cout << "����� ������� �����:  \"" << max_word << "\"" << endl
        << "����� �������� �����: \"" << min_word << "\"" << endl;
    system("pause");
    return 0;
}