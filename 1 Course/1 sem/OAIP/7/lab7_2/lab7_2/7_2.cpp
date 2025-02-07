#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	float b = 3, a = 6, i = 8, c = 6e-4, t, x;
	for (i; i <= 24; i += 4)
	{
		t = a * i / ((a * a) - b) * exp(-a);

		if (t > 5 * c)
			x = 4.8e-3 + i * a;
		else if (i <= 5 * c)
			x = a + (i * i) * t;
	}
	cout << x << endl;
	return 0;
}


	