//4lab
// Скопировать из файла FILE1 в файл FILE2 все строки, в которых более 2 слов.
//Определить номер слова, в котором больше всего гласных букв.

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_ALL, "rus");
    char buff[50];
    char g[] = "aeiouy";
    int z;
    int c = 0, k = 0, max = 0, gl = 0, u = 1, n;
    ofstream fout("a.txt"), fout2("b.txt");
    while (true)
    {
        cin.getline(buff, 512);
        if (buff[0] == ';') break;
        fout << buff;
        fout << "\n";
    }
    cout << "Количество введённых строк:";
    cin >> z;
    fout.close();
    ifstream fin("a.txt"), fin2("b.txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        for (int i = 0; i < z; i++) {
            k = 0;
            char buff[50];
            fin.getline(buff, 50);
            cout << buff << endl;
            cout << "----------------------------------------------------------------------------------" << endl;
            for (int i = 0; i < strlen(buff); i++) {
                if (buff[i] != ' ' && (buff[i + 1] == ' ' || buff[i + 1] == '\0'))
                    k++;
            }
            if (k == 2) {
                fout2 << buff << "\n"; c++;
            }
            buff[0] = 0;
        } fin.close();
    }fout2.close();

    if (!fin2.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        char s[100], str[100];
        for (int y = 0; y < c; y++) {

            fin2.getline(s, 100);
            for (char* p = strtok(s, " "); p; p = strtok(NULL, " "))
            {
                strcpy(str, p);
                for (int i = 0; i < strlen(str); ++i)
                {
                    for (int j = 0; j < strlen(g); ++j)
                    {
                        if (str[i] == g[j]) gl++;
                    }
                }
                if (gl > max) {
                    max = gl;
                    n = u;
                }
                u++;
            }
            s[0] = 0;
        }
        cout << "Номер слова с большим количеством гласных:" << n;
        fin2.close();
    }
}