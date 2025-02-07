// Написать программу, в которой нужно найти максимальный элемент вектора и вывести на экран.
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
	int  min;
    vector<int> vect;
    for (int i = 0; i < 7; i++)
        vect.push_back(20 - i); // добавляем числа в конец массива

    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << ' ';

    cout << '\n';

	min = vect[0];
	for (int i = 1; i < vect.size(); i++)
	{
		if (min > vect[i]) min = vect[i];
	}
	cout << "Min: " << min << endl;

	return 0;
}
