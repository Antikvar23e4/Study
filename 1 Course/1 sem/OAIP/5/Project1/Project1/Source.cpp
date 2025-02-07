#include <iostream>
#include <iomanip>

int main()
{
		setlocale(LC_CTYPE, "ru");
		int m = 6;
		double a = 2, b = 5e3, k, d, c;
		for (int i = 0; i < 1; i++) {
			a = 2;
			cout << "введите  k: ";
			cin >> k;
			while (a <= 2.8) {
				d = sin(k / a) / cos(m * b);
				c = d / ((d * d) + 1) * (1 - exp(k));
				a = a + 0.2;
				cout << d << endl << c << endl;
			}
		}
}

