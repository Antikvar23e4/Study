#include <iostream>
#include <iomanip> 
using namespace std;
void v1()
{
	setlocale(LC_CTYPE, "ru");
	int n, i, j;
	cout<<("Enter n: ");
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			printf("%5d", i * j);
		printf("\n");
		if (i == 1)
		{
			cout << endl;
			cout << setw(5 * n) << setfill('-') <<
				'-' << endl;
		}
	}
}

void v2()
{
	setlocale(LC_CTYPE, "ru");
	int m = 6;
	float a = 8, b = 5e3, k, d, c;
	cout << "Введите k: ";
	cin >> k;
	for (int i = 0; i < 2; i++); {
		d = sin(k / a) / cos(m * b);
		c = d / ((d * d) + 1) * (1 - exp(k));
		cout << d << endl << c << endl;
	}
}
void v3()
{
	setlocale(LC_CTYPE, "ru");
	int m = 6;
	double a = 8, b = 5e3, k=a, d, c;
	while (k<=3){
		d = sin(k / a) / cos(m * b);
		c = d / ((d * d) + 1) * (1 - exp(k));
		k = k - 0.5;
		cout << d << endl << c << endl;
	}
}
void v4()
{
	setlocale(LC_CTYPE, "ru");
	int m = 6;
	double a = 2, b = 5e3, k, d, c;
	for (int i = 0; i < 3; i++) {
		a = 2;
		cout << "Введите k: ";
		cin >> k;
	
		while (a <= 2.8) {
			d = sin(k / a) / cos(m * b);
			c = d / ((d * d) + 1) * (1 - exp(k));
			a = a + 0.2;
			cout << d << endl << c << endl;

		}
	}
}


void v5()
{
	setlocale(LC_CTYPE, "ru");
	//2
	int n;
	float p, sum = 0, s;
	cout << "Введите количество лет; n = ";
	cin >> n;
	cout << "Введите процент уценивания p = ";
	cin >> p;
	p = p / 100;
	for (int i = 1; i <= n; i++) {
		cout << "Стоимость оборудования за " << i << " год = ";
		cin >> s;
		sum += s;
		sum *= p;
	}
	cout << "Общая стоимость накопленного оборудования = " << sum << endl;
}


void v6()//1
{
	setlocale(LC_CTYPE, "ru");
	float p, q;
	int i = 0;
	cout << "Введите выручку в первый день: ";
	cin >> p;
	cout << "Введите максимальное значение: ";
	cin >> q;
	if (p <= q) {
	 do {
		p = p + 0.03 * p;
			i++;
		} while (p <= q);
		cout << "Выручка равна: " << p << endl << "Прошло " << i << " дней" << endl;
	}
	else {
		cout << "Выручка равна: " << p << endl << "Прошло 0 дней" << endl;
	}
}

void v7()
{
	    setlocale(LC_CTYPE, "ru");
		int a, i = 0, b;
		cout << "Введите числа: ";
		cin >> a;
		b = a / abs(a);
		cin >> a;
		while (a != 0) {
			if (b == a / abs(a)) {
				cin >> a;
			}
			else {
				b = a / abs(a);
				i++;
				cin >> a;
			}
		}
		cout << "Знак поменялся " << i << " раз";
}
int main()
{
	v1();
	v2();
	v3();
	v4();
	v5();
	v6();
	v7();
	return 0;
}
