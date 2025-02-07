//4lab
// Ввести с клавиатуры строку символов, состоящую из цифр и скобок, и записать ее в файл. 
//Прочитать из файла данные, посчитать и вывести количество скобок различного вида.

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_ALL, "rus");
    char buff[50];
    char l;
    int p; 
    int k = 0, j = 0;
    ofstream fout("t.txt");
    while (true)
    {
        cin.getline(buff, 512);
        if (buff[0] == ';') break;
        fout << buff;
        fout << "\n";
    }

    fout.close();
    ifstream fin("t.txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        char buff[50];
        char buff_new[] = ("("), buff_new2[] = (")");
        fin.getline(buff, 50);
        cout << "----------------------------------------------------------------------------------" << endl;
        for (int b = 0; b < strlen(buff); b++) {
            if (buff[b] == buff_new[0]) {
                k++;
            }
            if (buff[b] == buff_new2[0]) {
                j++;
            }
        }
        cout << "Открывающих *(* скобок в строке: " << k << endl;
        cout << "Закрывающих *)* скобок в строке: " << j << endl;
        fin.close();
    }
}
