#include <iostream>
#include "vybor2.h"
#include <windows.h>

	using namespace std;
	void vybor2()
	{
		char symbol1, symbol2;
		char symb1, symb_2;
		cout << "Введите прописную  и строчную букву русского алфавита: ";
		cin >> symb1 >> symb_2;
		cout  << symb1 - symb_2 << endl;
	}