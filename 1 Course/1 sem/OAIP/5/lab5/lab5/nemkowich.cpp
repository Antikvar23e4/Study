#include <iostream>
#include <iomanip>
using namespace std;

void v5()
{
	setlocale(LC_ALL, "ru");
	int K;
	cout << "Ведите число грибов: ";
	cin >> K;
	cout << "Мы нашли " << K;
	K %= 100;
	if (K > 20) K %= 10;

	if (K < 2)
		cout << " гриб ";
	else if (K < 5)
		cout << " гриба ";
	else
		cout << " грибов ";

	cout << "в лесу." << endl;

}

void v2()
{
	{
		setlocale(LC_CTYPE, "ru"); //Вычислить max(x + y + z, xyz) ∙ min(x, y, z)
		cout << "Введите три числа: ";
		float x, y, z, max, min;
		cin >> x >> y >> z;
		if ((x + y + z) < (x * y * z))
			max = (x * y * z);
		else 
			max = (x + y + z);
		min = x;
		if (min > y) min = y;
		if (min > z) min = z;
		cout << "max(x+y+z,x*y*z )*min(x, y, z)=" << max * min << endl;

	}
}
void v3()
{
     setlocale(LC_ALL, "ru");
 	int k;
 	puts("Вы хотите купить автомобиль? (1-да, 2-нет)");
	std::cin >> k;
	switch (k)
	{
	case 1: { puts("Какой? (1- Майбах, 2-Тойота, 3-Лада)");
		std::cin >> k;
		switch (k)
		{
		case 1: puts("Не слабо"); break;
		case 2: puts("Хороший выбор"); break;
		case 3: puts("Сомнительный выбор");
			break;
		}
		break;
	}
	case 2: puts("Полезно ходить пешком"); break;
	default: puts("Некорректный вариант"); break;
	}
}
void v4()
   //Вычислить max(x1+y1 , x1y1, y1*y2)+min(x1, y1, y2)

{
	setlocale(LC_CTYPE, "ru");

	cout << "Введите три числа: ";
	float x1, y1, y2, max, min;
	cin >> x1 >> y1 >> y2;

	if (x1 + y1 >= x1 * y1 && x1 + y1 >= y1 * y2)
		max = x1 + y1;
	else if (x1 * y1 >= x1 + y1 && x1 * y1 >= y1 * y2)
		max = x1 * y1;
	else
		max = y1 * y2;

	if (x1 + y1 <= x1 * y1 && x1 + y1 <= y1 * y2)
		min = x1 + y1;
	else if (x1 * y1 <= x1 + y1 && x1 * y1 <= y1 * y2)
		min = x1 * y1;
	else
		min = y1 * y2;

	cout << "max(x1+y1 , x1*y1, y1*y2)+min(x1, y1, y2)=" << max + min << endl;

	
}
void v6()
{
	setlocale(LC_CTYPE, "Russian");
	int k;
	std::puts("Вы хотите купить телефон? (1-да, 2-нет)");
	std::cin >> k;
	switch (k)
	{
	case 1: { puts("Какой? (1- Сяоми, 2-Айфон, 3-Самсунг)");
		std::cin >> k;
		switch (k)
		{
		case 1: puts("Лучший выбор:)"); break;
		case 2: puts("Лучший выбор:("); break;
		case 3: puts("Лучший выбор;)");
			break;
		}
		break;
	}
	case 2: puts("Правильно, телефон крадет много времени."); break;
	default: puts("Некорректный вариант."); break;
	}

}
void v73()
{    setlocale(LC_CTYPE, "Russian");
     float a, b, p, q, r, s;
     std::cout << "Введите размер застройки: ";
     cin >> a >> b;
     cout << "Ввдите размер первого здания: ";
     cin >> p >> q;
     cout << "Введите размер второго здания: ";
     cin >> r >> s;
  if ((p + r <= a && q <= b && s <= b) || (p + r <= b && q <= a && s <= a) || (p + s <= a && q <= b && r <= b) || (p + s <= b && q <= a && r <= a) || (q + r <= a && p <= b && s <= b) || (q + r <= b && p <= a && s <= a) || (q + s <= a && p <= b && r <= b) || (q + s <= b && p <= a && r <= a)) {
	cout << "На участке застройки можно разместить два здания.";
   }
  else {
	cout << "На участке застройки не поместятся два здания."<<endl;
    }
}


void v75()
{
	setlocale(LC_CTYPE, "ru");
	std::cout << "Введите длину, ширину и высоту коробки: ";
	float a, b, c, r, s, t;
	cin >> a >> b >> c;
	cout << endl << "Введите длину, ширину и высоту посылки: ";
	cin >> r >> s >> t;
	if (a >= r && b >= s && c >= t)
		cout << endl << "В коробку можно вместить посылку.";
	else
		cout << endl << "В коробку нельзя вместить посылку." << endl;

}
void v74()
{
	setlocale(LC_CTYPE, "ru");
	float r, p, q;
	std::cout << "Введите радиус шара: " << endl;
	cin >> r;
	cout << "Введите длины диагоналей ромба: ";
	cin >> p >> q;
	if (r <= (p / 2) * (q / 2) / sqrt(pow(p / 2, 2) + pow((q / 2.0), 2.0))) {
		cout << "Шар пройдет через отверстие.";
	}
	else {
		cout << "Шар не пройдет через отверстие.";
	}

}





int main()
{
	v4();
	v5();
	v2();
	v3();
	
	
	v6();
	v73();
	v75();
	v74();
	
	return 0;
}
