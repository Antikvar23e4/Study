#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	int x, a, b, c, d;
	x = 1000;
	while (x <= 9999) {
		a = x / 1000;
		b = (x % 1000) / 100;
		c = (x % 100) / 10;
		d = x % 10;

		if ((x % 2 == 0) && (x % 7 == 0) && (x % 11 == 0)) {
			if (a + b + c + d == 30) {
				if ((a == b && c == d) || (a == c && b == d) || (a == d && b == c)) {
					cout << x << endl;
				}
			}

		}
		x = x + 1;
	}
	system("pause");

}