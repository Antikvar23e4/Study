//Ввести с клавиатуры строку символов, состоящую из слов, разделенных пробелами, и записать ее в файл.
//Прочитать из файла данные и вывести все слова, которые содержат букву «р».
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_ALL, "rus");
    char buff[50];
    char g[] = "aeiouy";
    int p;
    int max = 0, min = 1000, gl = 0, gl2 = 0;       
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
    else {
        char s[50];
        while (!fin.eof()) {
            fin >> s;
            for (int x = 0; x < strlen(s); x++)
            {
                if (s[x] == 'p' || s[x] == 'P') cout << s << endl;
            }
            s[0] = 0;
        }
    }
    fin.close();
}
