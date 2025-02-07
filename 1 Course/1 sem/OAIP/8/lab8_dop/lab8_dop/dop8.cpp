#include <iostream>
#include <iomanip> 
using namespace std;
void v1()
	{
		setlocale(LC_CTYPE, "Russian");
		int a, n, sum;
		cout << "¬ведите число n: ";
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a;

			if (i % 2 == 0) {
				sum = sum + a;

			}

		}
		cout << "sum = " << sum << endl;

	}

void v2()
	{
	setlocale(LC_CTYPE, "Russian");
	int a, i, n, b, k;
	cout << "¬ведите количество чиел n = ";
	cin >> n;
	cout << "¬ведите числа: ";
	cin >> a;
	b = a / abs(a);
	k = 1;
	i = 0;
	while (k < n) {
		if (b == a / abs(a)) {
			cin >> a;
		}
		else {
			b = a / abs(a);
			i++;
			cin >> a;
		}
		k++;
	}
	cout << "«нак помен€лс€ " << i << " раз" << endl;
}
void v3()
{
	setlocale(LC_CTYPE, "Russian");
	int i, n, k;
	float min, max, a;
	cout << "¬ведите количество чиел n = " << endl;
	cin >> n;
	cout << "¬ведите числа: ";
	for (i = 1; i <= n; i++) {
		cin >> a;
		if (i == 1) {
			min = a;
			max = a;
		}
		if (a < min) {
			min = i;
		}
		if (a > max) {
			max = i;
		}

	}
	k = abs(max - min);
	cout << "ћежду максимальным и минимальным значением " << k << " чисел" << endl;
}

int main()
{
	v1();
	v2();
	v3();
	return 0;
}