#include <iostream>
#include <iomanip>


using namespace std;

void v13()

{

	setlocale(LC_ALL, "ru");

	char v;
	cout << "**13вариант,первое задание** " << endl << endl;
	cout << "Введите символ ";
	cin >> v;
	cout << setw(49) << setfill(' ') << ' ' << setw(7) << setfill(v) << v ;
	cout << setw(9) << setfill(' ') << ' ' << setw(7) << setfill(v) << v << endl;
	cout << setw(47) << setfill(' ') << ' ' << setw(10) << setfill(v) << v ;
	cout << setw(7) << setfill(' ') << ' ' << setw(10) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(13) << setfill(v) << v;
	cout << setw(5) << setfill(' ') << ' ' << setw(13) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(17) << setfill(v) << v;
	cout << setw(1) << setfill(' ') << ' ' << setw(17) << setfill(v) << v << endl;
	cout << setw(41) << setfill(' ') << ' ' << setw(39) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(35) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(31) << setfill(v) << v << endl;
	cout << setw(47) << setfill(' ') << ' ' << setw(27) << setfill(v) << v << endl;
	cout << setw(49) << setfill(' ') << ' ' << setw(23) << setfill(v) << v << endl;
	cout << setw(51) << setfill(' ') << ' ' << setw(19) << setfill(v) << v << endl;
	cout << setw(53) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(55) << setfill(' ') << ' ' << setw(11) << setfill(v) << v << endl;
	cout << setw(57) << setfill(' ') << ' ' << setw(7) << setfill(v) << v << endl;
	cout << setw(59) << setfill(' ') << ' ' << setw(3) << setfill(v) << v << endl;
	cout << setw(60) << setfill(' ') << ' ' << setw(1) << setfill(v) << v << endl;

	
}

void v132()
{
	cout << "**13вариант,второе задание** " << endl << endl;
	int n, i = 2; std::cout << "n = "; std::cin >> n;
	double m; std::cout << "m = "; std::cin >> m;
	m *= 60;
	double curr = m, sum = m;
	while (i <= n) {
		curr += 10;
		sum += curr;
		i++;
	}
	sum /= 60;
	std::cout <<"Вся бригада работала:" << sum << "\n";
	system("pause");
	
}

void v5()

{

	setlocale(LC_ALL, "Russian");

	char v;
	cout << "**5вариант,первое задание **" << endl << endl;
	cout << "Введите символ: ";

	cin >> v;
	cout << setw(59) << setfill(' ') << ' ' << setw(2) << setfill(v) << v << endl;
	cout << setw(58) << setfill(' ') << ' ' << setw(4) << setfill(v) << v << endl;
	cout << setw(57) << setfill(' ') << ' ' << setw(6) << setfill(v) << v << endl;
	cout << setw(56) << setfill(' ') << ' ' << setw(8) << setfill(v) << v << endl;
	cout << setw(55) << setfill(' ') << ' ' << setw(10) << setfill(v) << v << endl;
	cout << setw(54) << setfill(' ') << ' ' << setw(12) << setfill(v) << v << endl;
	cout << setw(53) << setfill(' ') << ' ' << setw(14) << setfill(v) << v << endl;
	cout << setw(52) << setfill(' ') << ' ' << setw(16) << setfill(v) << v << endl;
	cout << setw(51) << setfill(' ') << ' ' << setw(18) << setfill(v) << v << endl;
	cout << setw(50) << setfill(' ') << ' ' << setw(20) << setfill(v) << v << endl;
	cout << setw(49) << setfill(' ') << ' ' << setw(22) << setfill(v) << v << endl;
	cout << setw(48) << setfill(' ') << ' ' << setw(24) << setfill(v) << v << endl;
	cout << setw(47) << setfill(' ') << ' ' << setw(26) << setfill(v) << v << endl;
	cout << setw(46) << setfill(' ') << ' ' << setw(28) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(30) << setfill(v) << v << endl;
	cout << setw(44) << setfill(' ') << ' ' << setw(32) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(34) << setfill(v) << v << endl;
	cout << setw(42) << setfill(' ') << ' ' << setw(36) << setfill(v) << v << endl;
	cout << setw(41) << setfill(' ') << ' ' << setw(38) << setfill(v) << v << endl;
	cout << setw(40) << setfill(' ') << ' ' << setw(40) << setfill(v) << v << endl;
	cout << setw(39) << setfill(' ') << ' ' << setw(42) << setfill(v) << v << endl;
	cout << setw(38) << setfill(' ') << ' ' << setw(44) << setfill(v) << v << endl;
	cout << setw(37) << setfill(' ') << ' ' << setw(46) << setfill(v) << v << endl;
	cout << setw(36) << setfill(' ') << ' ' << setw(48) << setfill(v) << v << endl;
	cout << setw(35) << setfill(' ') << ' ' << setw(50) << setfill(v) << v << endl;
	cout << setw(34) << setfill(' ') << ' ' << setw(52) << setfill(v) << v << endl;

	
}
void v52()
{
	setlocale(LC_ALL, "ru");
	cout << "**5вариант,второе задание** " << endl << endl;
	float ps, milk, milksum, milkwin, years;
	cout << "Введите стоимость молока: ";
	cin >> milk;
	cout << endl << "На сколько процентов должна подняться стоимость молока? ";
	cin >> ps;
	cout << endl << "Через какое число лет вы хотите узнать результат? \t";
	cin >> years;

	ps *= 0.01;

	for (int i = 0; i < years; i++)
	{
		milkwin = ps * milk + milk;
		cout << "Стоимость молока зимой №" << i + 1 << " равна: " << milkwin << endl;
		milksum = milkwin - ps * milkwin;
		cout << "Стоимость молока летом №" << i + 1 << " равна: " << milksum << endl;
	}


	if (milkwin > milksum)
		cout << "Стоимость молока зимой №" << years << " была выше на " << milkwin - milksum;
	else if (milksum > milkwin)
		cout << "Стоимость молока летом №" << years << " была выше на " << milksum - milkwin;
	else
		cout << "Стоимость молока летом №" << years << " равна стоимости молока зимой №" << years;

	
}
void v2()

{
	setlocale(LC_ALL, "ru");

	char v;
	cout << "**2вариант,первое задание**" << endl << endl;
	cout << "Введите символ ";

	cin >> v;
	cout << setw(45) << setfill(' ') << ' ' << setw(30) << setfill(v) << v << endl;
	cout << setw(44) << setfill(' ') << ' ' << setw(32) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(34) << setfill(v) << v << endl;
	cout << setw(42) << setfill(' ') << ' ' << setw(36) << setfill(v) << v << endl;
	cout << setw(41) << setfill(' ') << ' ' << setw(38) << setfill(v) << v << endl;
	cout << setw(40) << setfill(' ') << ' ' << setw(40) << setfill(v) << v << endl;
	cout << setw(41) << setfill(' ') << ' ' << setw(38) << setfill(v) << v << endl;
	cout << setw(42) << setfill(' ') << ' ' << setw(36) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(34) << setfill(v) << v << endl;
	cout << setw(44) << setfill(' ') << ' ' << setw(32) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(30) << setfill(v) << v << endl;

	
}




void v15()

{
	setlocale(LC_ALL, "ru");

	char v;

	cout << "Введите символ " << endl << endl;

	cin >> v;

	cout << setw(51) << setfill(' ') << ' ' << setw(2) << setfill(v) << v << endl;
	cout << setw(50) << setfill(' ') << ' ' << setw(4) << setfill(v) << v << endl;
	cout << setw(49) << setfill(' ') << ' ' << setw(6) << setfill(v) << v << endl;
	cout << setw(48) << setfill(' ') << ' ' << setw(8) << setfill(v) << v << endl;
	cout << setw(47) << setfill(' ') << ' ' << setw(10) << setfill(v) << v << endl;
	cout << setw(46) << setfill(' ') << ' ' << setw(12) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(14) << setfill(v) << v << endl;
	cout << setw(44) << setfill(' ') << ' ' << setw(16) << setfill(v) << v << endl;
	cout << setw(43) << setfill(' ') << ' ' << setw(18) << setfill(v) << v << endl;
	cout << setw(42) << setfill(' ') << ' ' << setw(20) << setfill(v) << v << endl;
	cout << setw(41) << setfill(' ') << ' ' << setw(22) << setfill(v) << v << endl;
	cout << setw(40) << setfill(' ') << ' ' << setw(24) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;
	cout << setw(45) << setfill(' ') << ' ' << setw(15) << setfill(v) << v << endl;

}

void v152()
{
	setlocale(LC_ALL, "ru");
	cout << "**9вариант,второе задание** " << endl << endl;
	int k, podezd, ostatok,etaz;
		cout <<"Введите номер квартиры k: ";
		cin >> k;
		 podezd = (k- 1) / 36 + 1;
		 ostatok = (k - 1) % (9 * 4);
		 etaz = ostatok / 4 + 1;
		 cout << "Номер подъезда:" << podezd << "\n" << endl;
		 cout << "номер этажа:" << etaz << "\n" << endl;
}
		
 void v22()
		 {
             setlocale(LC_ALL, "ru");
			 cout << "**2вариант,второе задание**" << endl << endl;
			 float m, m1, m2;
			 cout << "Введите число m: " << endl << endl;
			 cin >> m;
			 double x = (m - 5) / 2; //Вычисляем меньшее число
			 double y = x + 5; //И большее
			 cout << x << ", " << y; //Выводим оба числа
 }

		

int main()
{
	v13();
	v132();
	v5();
	v52();
	v2();
	v22();
	v15();
	v152();
	return 0;
}