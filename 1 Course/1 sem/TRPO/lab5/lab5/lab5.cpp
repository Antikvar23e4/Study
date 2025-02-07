#include <iostream>
void main(){

	using namespace std;
	setlocale(LC_ALL, "ru");
	int n;
	char symbol1, symbol2;
	char symb1, symb_2;
	cout << "¬ыберите один из вариантов:" << endl;
		cout << "\n1 Ц определение разницы значений кодов в Windows-1251 буквы латинского алфавита в прописном и строчном написании;" << endl;
		cout << "\n2 Ц определение разницы значений кодов в Windows-1251 буквы русского алфавита в прописном и строчном написании;" << endl;
		cout << "\n3 Ц вывод в консоль кода символа, соответствующего введенной цифре;" << endl;
		cout << "\n4 Ц выход из программы." << endl;
	cin >> n;
	while (n > 4 && n < 1) {
		cout << "¬ведите ваш символ: ";  cin >> n;
	}
	switch (n) {
	case 1:
		cout << "¬ведите букву латинского алфавита в строчном и прописном виде: ";
		cin >> symbol1 >> symbol2;
		while (int(symbol1) < int('a') || int(symbol1) > int('z') || int(symbol2) < int('A') || int(symbol2) > ('Z') || abs(symbol1 - symbol2) != 32) {
			cout << "¬ведите букву латинского алфавита в строчном и прописном виде: ";
			cin >> symbol1 >> symbol2;
		}
		cout << "–азница равна = " << symbol1 - symbol2 << endl;
		break;
	case 2:
		cout << "¬ведите букву русского алфавита в строчном и прописном виде: ";
		cin >> symb1 >> symb_2;
		cout << "–азница равна = " << symb1 - symb_2 << endl;
		break;
	case 3:
		char sym;
		cout << "¬ведите любую цифру от 1 до 9: "; cin >> sym;
		while (sym > '9' || sym < '0') {
			cout << "\n¬ведите число: " << endl;
			cin >> sym;
		}
		cout << int(sym);
		break;
	case 4:
		break;
	}
}