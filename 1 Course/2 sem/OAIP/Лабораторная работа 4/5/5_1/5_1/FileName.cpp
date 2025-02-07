//Скопировать из файла FILE1 в файл FILE2 строки, начиная с четвертой по порядку. Подсчитать ко-личество символов в последнем слове FILE2.
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");

    int n = 4;
    char str[25];
    int pos = 0;

    ifstream in("in.txt"); // read
    ofstream out("out.txt"); // write

    char ch;
    // проходим по файлу и отсчитываем 4 строчки
    while (in.good() && n)
    {
        ch = in.get();
        if (ch == '\n')
            n--;
    }

    cout << "\nВ файл скопировано: " << endl;
    while (in.good() && !in.eof())
    {
        ch = in.get();
        if (ch == '\n') {
            cout << endl;
            pos = 0;
        }
        if (ch == ' ')
        {
            pos = 0;
        }
        pos++;
        cout << ch;
        out << ch;
    }
    pos -= 2;
    cout << "\nКоличество символов в последнем словеыа  равно: " << pos << endl;
}