//Написать программу, в которой нужно найти сумму минимального и максимального элементов массива, с выводом на экран.
#include <iostream>
#include <array>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
	int  max, min, sum;

    array<int, 4> newarray = { 5, 16, 6, 7 };
	for (int i = 0; i < newarray.size(); i++)
		cout << newarray[i] << ' ';

	cout << '\n';

	max = newarray[0];
	min = newarray[0];
	for (int i = 1; i < newarray.size(); i++)
	{
		if (max < newarray[i]) max = newarray[i];
		if (min > newarray[i]) min = newarray[i];
	}
	cout << "Min: " << min << endl;
	cout << "Max: " << max << endl;
	cout << "Sum: " << max + min << endl;
}
