#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "ru");
	float x, y, sum = 0;
	int t = 0.5;
	cout << "¬ведите x" <<  endl;
	cin >> x;
	for (int i = 1; i < 5; i++) {
		cout << "¬ведите x" << endl;
		cin >> x;
		sum = pow(x, 2) + t;
	}
	while (t <= 3) {
		if (t > 2) {
			y = sum;
		}
		else  if (t <= 2) {
			y = cos(pow(t, 2));
		}
		cout << "y = " << y << endl;
		t = t + 0.5;

		return 0;
	}
}




