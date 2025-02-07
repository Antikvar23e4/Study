
#include <iostream>
#include "vybor1.h"
#include "vybor2.h"
#include "vybor3.h"


void main()
{
	using namespace std;
	setlocale(LC_ALL, "ru");
	int n;
	char symbol1, symbol2;
	char symb1, symb_2;
	cout << "¬ыберите один из вариантов:\n1 Ц определение разницы значений кодов в Windows-1251 буквы латинского алфавита в прописном и строчном написании; \n2 Ц определение разницы значений кодов в Windows-1251 буквы русского алфавита в прописном и строчном написании; \n3 Ц вывод в консоль кода символа, соответствующего введенной цифре; \n4 Ц выход из программы." << endl;
	cin >> n;
	while (n > 4 && n < 1) {
		cout << "¬ведите ваш символ: ";  cin >> n;
	}
	switch (n) {
	case 1:
		vybor1();
		break;
	case 2:
		vybor2();
		break;
	case 3:
		vybor3();
		break;
	case 4:
		break;
	default:
		break;
	}
}