#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "ru");
	double d, y, y1, q,sum=0;
	cout << "Введите y" << endl;
	cin >> y;
	cout << " " << endl;
	for (int i = 1; i < 5; i++)
		cin >> y1;
	if (y1 < y) {
		d = y1;
	}
	cout << "Минимальнй y = " << d << endl;
	for (int h=1;h<=5;h++){
		sum += 4 * y + d;
	}
	q = sum;
	cout << "d = " << d << endl;
	cout << "q = " << q << endl << endl;
	return 0;
}

