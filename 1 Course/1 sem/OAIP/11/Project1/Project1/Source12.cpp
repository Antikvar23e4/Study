#include <iostream>
#include <clocale>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void main()
{
    setlocale(LC_ALL, "Russian");
    FILE* f1 = fopen("file.txt", "r+");
    FILE* f2 = fopen("out.txt", "w");
    if (f1 == NULL)
    {
        cout << "Нет такого файла" << endl;
        exit(1);
    }
    char* p;
    int cleth;
    char str[255];
    int key = 3, lang;
    for (int i = 0; i > -100; i--)
    {
        cout << "Letter=" << (char)i << " code= " << i << endl;
    }

    cout << "Какой язык?\n1 - Английский\n2 - Русский\n";
    do {
        cin >> lang;
        if (lang < 1 || lang>2)
        {
            cout << "Введите 1 или 2\n";
        }
    } while (lang < 1 || lang>2);
    cout << "Введите ключ\n";
    do {
        cin >> key;
        if (lang == 1 && key < 1 || key>25 && lang == 1)
        {
            cout << "Ключ может быть от 1 до 25:\n";
        }
        if (lang == 2 && key < 1 || key>32 && lang == 2)
        {
            cout << "Ключ может быть от 1 до 32:\n";
        }
    } while (key < 1 || key>25 && lang == 1 || key > 32 && lang == 2);
    while (!feof(f1))
    {
        fgets(str, 254, f1);
        cleth = strlen(str);
        p = new char[cleth];
        p[cleth] = '\0';
        for (int i = 0; i < cleth; i++)
        {
            cout << "Letter=" << str[i] << " code= " << (int)str[i] << endl;
            if ((int)str[i] <= 90 && (int)str[i] >= 65 && lang == 1)
            {
                if ((int)str[i] + key <= 90)
                {
                    p[i] = (int)str[i] + key;
                }
                if ((int)str[i] + key > 90)
                {
                    p[i] = 64 + (int)str[i] + key - 90;
                }
            }
            else
                if ((int)str[i] <= 122 && (int)str[i] >= 97 && lang == 1)
                {
                    if ((int)str[i] + key <= 122)
                    {
                        p[i] = (int)str[i] + key;
                    }
                    if ((int)str[i] + key > 122)
                    {
                        p[i] = 96 + (int)str[i] + key - 122;
                    }
                }
                else
                    if ((int)str[i] <= -33 && (int)str[i] >= -64 && lang == 2)
                    {
                        if ((int)str[i] + key <= -33)
                        {
                            p[i] = (int)str[i] + key;
                        }
                        if ((int)str[i] + key > -33)
                        {
                            p[i] = -34 + (int)str[i] + key + 64;
                        }
                    }
                    else
                        if ((int)str[i] <= -1 && (int)str[i] >= -32 && lang == 2)
                        {
                            if ((int)str[i] + key <= -1)
                            {
                                p[i] = (int)str[i] + key;
                            }
                            if ((int)str[i] + key > -1)
                            {
                                p[i] = -2 + (int)str[i] + key + 32;
                            }
                        }
                        else
                        {
                            p[i] = str[i];
                        }
        }
        fprintf(f2, "%s\n", p);
    }
    fclose(f1);
    fclose(f2);
}
