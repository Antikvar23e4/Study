#include <iostream> 
using namespace std;
 
void v13_1() 
{
	setlocale(LC_CTYPE, "rus");
	char tmp[33];
	int A, B;
	cout << "Введите A: ", cin >> A;
	cout << "Введите B: ", cin >> B;

	_itoa_s(A, tmp, 2); cout << "Число A:" << tmp << endl;
	_itoa_s(B, tmp, 2); cout << "Число B:" << tmp << endl;

	if (A & (1 << 5)) {
		B |= (1 << 5);
	}
	else B &= ~(1 << 5);

	if (A & (1 << 6)) B |= (1 << 6);
	else B &= ~(1 << 6);
	_itoa_s(B, tmp, 2); cout << "B:" << tmp << endl;

}

void v13_2()
{
	setlocale(LC_CTYPE, "rus");
	char tmp[33];
	int A, n, p;
	cout << "Введите A: ", cin >> A;
	cout << "Введите p: ", cin >> p;
	cout << "Введите n: ", cin >> n;
	_itoa_s(A, tmp, 2); cout << "Число A:" << tmp << endl;

	for (int i = 0; i < n; i++) {

		A ^= (1 << p);
		p--;
	}
	_itoa_s(A, tmp, 2);
	cout << "A = " << tmp << endl;

}


void v10_1()
{
	setlocale(LC_CTYPE, "Russian");
    char tmp[33];
	int A = 693, MaskA = 508;
	_itoa_s(A, tmp, 2);
		cout << "Число А в двоичной системе: " << tmp << endl;
	_itoa_s(MaskA, tmp, 2);
		cout << "Маска числа А:" << tmp << endl;
	_itoa_s((A&MaskA) >> 2, tmp, 2);
		cout << "Результат: " << tmp << endl;
}

void v10_2()
{
	setlocale(LC_CTYPE, "Russian");
		char tmp[33];
		int n, p, A, MaskA;
		cout << "Число А:"; cin >> A;
		cout << "С какой позиции:"; cin >> p;
		cout << "Сколько позиций: "; cin >> n;
		MaskA = (1u << n) - 1;
		MaskA  <<= (p - 1);
	_itoa_s(MaskA, tmp, 2);
		cout << "Число Maska в двоичной системе: " << tmp << endl;
	_itoa_s(A, tmp, 2);
		cout << "Число A в двоичной системе:" << tmp << endl;
    	cout << "Маска числа А в двоичной системе:" << tmp << endl;
	_itoa_s(A&(~MaskA), tmp, 2);
		cout << "Результат: " << tmp << endl;
}


void v11_1()
{
	setlocale(LC_CTYPE, "Russian");
		int A, i; char tmp[33];
		cout << "Введите число: ";
		cin >> A;
		_itoa_s(A, tmp, 2);
	
		cout << "Число в двоичном виде:" << tmp << endl;
		if ((A & 15) == 0)
			cout << "Число кратно 16." << endl;
		else
			cout << "Число не кратно 16." << endl;
}



void v11_2()
{
	setlocale(LC_CTYPE, "Russian");
	char tmp[33];
	int A, B, MaskA = 0, MaskB = 0, n, p, m, q;
	cout << "Сколько позиций:"; cin >> n;
	cout << "С какой позиции:"; cin >> p;
	cout << "Число А: "; cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "Число А в двоичной системе:" << tmp << endl;
	for (int i = p - 1; i < n + p - 1; i++)
	{
		MaskA += pow(2, i);
	}
	cout << "Маска в десятичной системе:" << MaskA << endl;
	_itoa_s(MaskA, tmp, 2);
	cout << "Маска в двоичной системе:" << tmp << endl;
	MaskA >>= p - 1;
	_itoa_s(A ^ MaskA, tmp, 2);
	cout << " A:" << tmp << endl;

	cout << "Сколько позиций:"; cin >> m;
	cout << "С какой позиции:"; cin >> q;
	cout << "Число B:"; cin >> B;
	_itoa_s(A, tmp, 2);
	cout << "Число B в двоичной системе:" << tmp << endl;
	for (int k = q - 1; k < m + q - 1; k++)
	{
		MaskB += pow(2, k);
	}
	cout << "Маска в десятичной системе:" << MaskB << endl;
	_itoa_s(MaskB, tmp, 2);
	cout << "Маска в двоичной системе:" << tmp << endl;
	MaskB >>= q - 1;
	_itoa_s(B ^ MaskB, tmp, 2);
	cout << "B:" << tmp << endl;
	
}



void v12_1()
{
	setlocale(LC_CTYPE, "ru");
		unsigned short int A;
		char tmp[33];
		cout << "Введите число А:"; cin >> A;
	_itoa_s(A, tmp, 2);
		cout << tmp << " - двоичный вид числа А " << endl;
		A = ~A; 
	_itoa_s(A, tmp, 2);
		const unsigned int maskA = 65287;
		_itoa_s(maskA, tmp, 2);
		A =(A^maskA);
	_itoa_s(A, tmp, 2);
		cout << tmp <<" Число с инвертированными битами (с 4 по 8 включительно) " <<endl;
}

void v12_2()
{
	setlocale(LC_CTYPE, "ru");
		char tmp[33];
		int A, B, n, p, q, A1;
	    cout << "Введите число A: ", cin >> A, cout << endl;
	_itoa_s(A, tmp, 2);
		cout << "Число А в двоичной системе: " << tmp << endl;
		cout << "Введите количество битов и номер позиции, с которой нужно устанавливать биты в 0 ", cin >> n >> p, cout << endl;
		unsigned int maskA = A;
		for (int i = p - n; i < p; i++) 
		{
			A &= ~(1 << i);
		_itoa_s(A, tmp, 2); 
			cout << "Число A после изменения: " << tmp << endl;
		}
		if (A == maskA)
			cout << "Число не изменилось " << endl;
		A1 = (A ^ maskA) >> (p - n);
	_itoa_s(A1, tmp, 2);
		cout << "Число A1 " << tmp << endl;
	
		cout << "Введите число B: ", cin >> B, cout << endl;
	_itoa_s(B, tmp, 2);
		cout << "Число B в двоичной системе: " << tmp << endl;
		cout << "Введите позицию, с которой нужно менять биты ", cin >> q, cout << endl;
		A1 = A1 << (q - n);
	_itoa_s(A1, tmp, 2);
		cout << "Число A1:" << tmp << endl;
		unsigned int maskB = ~A1;
		B = (B & maskB) | A1;
	_itoa_s(B, tmp, 2);
		cout << "Конечное число:" << tmp << endl;
}

int main()
{
	v13_1();
	v13_2();
	v10_1();
	v10_2();
	v11_1();
	v11_2();
	v12_1();
	v12_2();

}
