#include <iostream>
#include "vybor3.h"
#include <windows.h>

using namespace std;
void vybor3()
	{
		char symbol1, symbol2;
		char symb1, symb_2;
		char sym;
		cout << "Введите любую цифру от 1 до 9: "; cin >> sym;
		while (sym > '9' || sym < '0') {
			cout << "\n... " << endl;
			cin >> sym;
		}
		cout << int(sym);
	}
