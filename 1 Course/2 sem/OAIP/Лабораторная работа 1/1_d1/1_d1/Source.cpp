#include<iostream>
using namespace std;
#define SIZE 3

struct StudentsExam {
    char fio[4];
    int exam[5];
    int estimation[5];
};

StudentsExam stud[SIZE];

void highScores();

int main()
{
    setlocale(LC_CTYPE, "rus");
    int kolich = 0;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "������� ���: ";
        cin >> stud[i].fio;
        cout << "������� ����� �� ��������� ���������: \n";
        cout << "���� | ��� | ������ | �� | ��� \n";

        for (int j = 0; j < 5; j++)
        {
            cin >> stud[i].estimation[j];
        }
    };
    highScores();
    return 0;
}

void highScores() {
    float kolichHighScores, kolichStudentsHighScores = 0, percent;
    for (int i = 0; i < SIZE; i++) {
        kolichHighScores = 0;
        for (int j = 0; j < 5; j++) {
            if (stud[i].estimation[j] > 3) {
                kolichHighScores++;
            }
        }
        if (kolichHighScores == 5) {
            kolichStudentsHighScores++;
        }
    }
    percent = (kolichStudentsHighScores / SIZE) * 100;
    cout << "��������� ����� ���������, ������� �������� �� 4 � 5, � ������ ����� ��������� " << percent << "%";
}