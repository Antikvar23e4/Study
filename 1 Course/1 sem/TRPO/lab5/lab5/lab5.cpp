#include <iostream>
void main(){

	using namespace std;
	setlocale(LC_ALL, "ru");
	int n;
	char symbol1, symbol2;
	char symb1, symb_2;
	cout << "�������� ���� �� ���������:" << endl;
		cout << "\n1 � ����������� ������� �������� ����� � Windows-1251 ����� ���������� �������� � ��������� � �������� ���������;" << endl;
		cout << "\n2 � ����������� ������� �������� ����� � Windows-1251 ����� �������� �������� � ��������� � �������� ���������;" << endl;
		cout << "\n3 � ����� � ������� ���� �������, ���������������� ��������� �����;" << endl;
		cout << "\n4 � ����� �� ���������." << endl;
	cin >> n;
	while (n > 4 && n < 1) {
		cout << "������� ��� ������: ";  cin >> n;
	}
	switch (n) {
	case 1:
		cout << "������� ����� ���������� �������� � �������� � ��������� ����: ";
		cin >> symbol1 >> symbol2;
		while (int(symbol1) < int('a') || int(symbol1) > int('z') || int(symbol2) < int('A') || int(symbol2) > ('Z') || abs(symbol1 - symbol2) != 32) {
			cout << "������� ����� ���������� �������� � �������� � ��������� ����: ";
			cin >> symbol1 >> symbol2;
		}
		cout << "������� ����� = " << symbol1 - symbol2 << endl;
		break;
	case 2:
		cout << "������� ����� �������� �������� � �������� � ��������� ����: ";
		cin >> symb1 >> symb_2;
		cout << "������� ����� = " << symb1 - symb_2 << endl;
		break;
	case 3:
		char sym;
		cout << "������� ����� ����� �� 1 �� 9: "; cin >> sym;
		while (sym > '9' || sym < '0') {
			cout << "\n������� �����: " << endl;
			cin >> sym;
		}
		cout << int(sym);
		break;
	case 4:
		break;
	}
}