//Ввести с клавиатуры две строки символов, состоящих из слов, разделенных пробелами, и записать их в файл. 
//Прочитать из файла данные. Найти самое короткое слово в первой строке и самое длинное во второй строке. Посчитать количество гласных букв в этих словах. 
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
    ofstream file;          // поток для записи
    file.open("file.txt"); // окрываем файл для записи
    if (file.is_open())
    {
        file << "Lorem ipsum dolor sit amet, consectetuer adipiscing elit" << endl;
        file << "Aenean commodo ligula eget dolor" << endl;

    }
    file.close();

    cout << "Содержимое файла: " << endl;
    ifstream in("file.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
    in.close();     // закрываем файл
    cout << endl;
    string word, max_word, min_word;
    size_t len, max_len = 0, min_len = 1000;
    ifstream find("file.txt");

    while (find) {
        word = get_word(find);
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

    find.close();
    cout << endl;

    cout << "Самое длинное слово во второй строке:  " << max_word << endl
        << "Самое короткое слово в первой строке: " << min_word << endl;

    unsigned char g[20] = { 'a','e','u','o','i','y' };
    int j, k, m, n, c[256], z[256];
    memset(c, 0, sizeof(int) * 256);
    memset(z, 0, sizeof(int) * 256);

    for (k = j = 0; j - max_word.length();
        c[(unsigned char)max_word[j++]]++);
    cout << endl;
    for (j = 0; j - 20; k += c[g[j++]]);
    cout << "Количество гласных в первом слове: " << k << endl;
    for (m = n = 0; n - min_word.length();
        z[(unsigned char)min_word[n++]]++);

    for (n = 0; n - 20; m += z[g[n++]]);
    cout << "Количество гласных во втором  слове: " << m << endl;
    cout << endl;
    system("pause");
    return 0;
}