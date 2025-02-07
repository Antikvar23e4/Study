//Скопировать из файла FILE1 в файл FILE2 все строки, в которых нет слов, совпадающих с первым словом. 
//Определить количество согласных букв в первой строке  файла FILE2.
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_ALL, "rus");
    char buff[50]; char l; int p; int sgl = 0;       
    ofstream fout("t.txt"), fout2("b.txt");   
    while (true)
    {
        cin.getline(buff, 512);


        if (buff[0] == ';') break;
        fout << buff;
        fout << "\n";
    }
    cout << "Количество введённых строк:"; cin >> p;

    fout.close();
    ifstream fin("t.txt");  
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        for (int i = 0; i < p; i++) {
            char buff[50]; char buff_new[50];
            fin >> buff_new;
            cout << buff_new << endl;
            fin.getline(buff, 50);
            cout << buff << endl;
            if (!strstr(buff, buff_new)) {
                fout2 << buff_new << "" << buff << "\n";
            }

            buff[0] = 0;
            buff_new[0] = 0;
           
        } fin.close();
    }fout2.close();
    ifstream fin2("b.txt");
    if (!fin2.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        cout << "Первая строка:" << endl;
        char s[] = ("bcdfghjklmnpqrstvwxz");
        char buff2[50];
        fin2.getline(buff2, 50);
        cout << buff2 << endl;
        for (int i = 0; i < strlen(buff2); ++i)
        {

            for (int j = 0; j < strlen(s); ++j)
            {
                if (buff2[i] == s[j]) sgl++;
            }
        }
        cout << "Согласных букв в строке: " << sgl << endl;

    }
    fin2.close();
}