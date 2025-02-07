//Ввести с клавиатуры строку, состоящую из букв, цифр, запятых, точек, знаков + и , и записать ее в файл. 
//Прочитать из файла данные и вывести подстроку, которая соответствует записи целого числа.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    setlocale(LC_CTYPE, "rus");
    string str;


    ofstream out("out2.txt"); // write


    // проходим по файлу и отсчитываем 4 строчки

    cout << "Введите строку с клавиатуры\n";
    getline(cin, str);
    out << str;
    out.close();

    char ch;
    ifstream in("out2.txt"); // read
    while (in.good() && !in.eof())
    {
        ch = in.get();

        if (ch >= '0' && ch <= '9')
        {
            cout << ch;
        }
    }

    ;
}