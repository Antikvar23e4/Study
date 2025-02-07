#include <iostream> 
using namespace std;
 
void v13_1() 
{
	setlocale(LC_CTYPE, "rus");
	char tmp[33];
	int A, B;
	cout << "������� A: ", cin >> A;
	cout << "������� B: ", cin >> B;

	_itoa_s(A, tmp, 2); cout << "����� A:" << tmp << endl;
	_itoa_s(B, tmp, 2); cout << "����� B:" << tmp << endl;

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
	cout << "������� A: ", cin >> A;
	cout << "������� p: ", cin >> p;
	cout << "������� n: ", cin >> n;
	_itoa_s(A, tmp, 2); cout << "����� A:" << tmp << endl;

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
		cout << "����� � � �������� �������: " << tmp << endl;
	_itoa_s(MaskA, tmp, 2);
		cout << "����� ����� �:" << tmp << endl;
	_itoa_s((A&MaskA) >> 2, tmp, 2);
		cout << "���������: " << tmp << endl;
}

void v10_2()
{
	setlocale(LC_CTYPE, "Russian");
		char tmp[33];
		int n, p, A, MaskA;
		cout << "����� �:"; cin >> A;
		cout << "� ����� �������:"; cin >> p;
		cout << "������� �������: "; cin >> n;
		MaskA = (1u << n) - 1;
		MaskA  <<= (p - 1);
	_itoa_s(MaskA, tmp, 2);
		cout << "����� Maska � �������� �������: " << tmp << endl;
	_itoa_s(A, tmp, 2);
		cout << "����� A � �������� �������:" << tmp << endl;
    	cout << "����� ����� � � �������� �������:" << tmp << endl;
	_itoa_s(A&(~MaskA), tmp, 2);
		cout << "���������: " << tmp << endl;
}


void v11_1()
{
	setlocale(LC_CTYPE, "Russian");
		int A, i; char tmp[33];
		cout << "������� �����: ";
		cin >> A;
		_itoa_s(A, tmp, 2);
	
		cout << "����� � �������� ����:" << tmp << endl;
		if ((A & 15) == 0)
			cout << "����� ������ 16." << endl;
		else
			cout << "����� �� ������ 16." << endl;
}



void v11_2()
{
	setlocale(LC_CTYPE, "Russian");
	char tmp[33];
	int A, B, MaskA = 0, MaskB = 0, n, p, m, q;
	cout << "������� �������:"; cin >> n;
	cout << "� ����� �������:"; cin >> p;
	cout << "����� �: "; cin >> A;
	_itoa_s(A, tmp, 2);
	cout << "����� � � �������� �������:" << tmp << endl;
	for (int i = p - 1; i < n + p - 1; i++)
	{
		MaskA += pow(2, i);
	}
	cout << "����� � ���������� �������:" << MaskA << endl;
	_itoa_s(MaskA, tmp, 2);
	cout << "����� � �������� �������:" << tmp << endl;
	MaskA >>= p - 1;
	_itoa_s(A ^ MaskA, tmp, 2);
	cout << " A:" << tmp << endl;

	cout << "������� �������:"; cin >> m;
	cout << "� ����� �������:"; cin >> q;
	cout << "����� B:"; cin >> B;
	_itoa_s(A, tmp, 2);
	cout << "����� B � �������� �������:" << tmp << endl;
	for (int k = q - 1; k < m + q - 1; k++)
	{
		MaskB += pow(2, k);
	}
	cout << "����� � ���������� �������:" << MaskB << endl;
	_itoa_s(MaskB, tmp, 2);
	cout << "����� � �������� �������:" << tmp << endl;
	MaskB >>= q - 1;
	_itoa_s(B ^ MaskB, tmp, 2);
	cout << "B:" << tmp << endl;
	
}



void v12_1()
{
	setlocale(LC_CTYPE, "ru");
		unsigned short int A;
		char tmp[33];
		cout << "������� ����� �:"; cin >> A;
	_itoa_s(A, tmp, 2);
		cout << tmp << " - �������� ��� ����� � " << endl;
		A = ~A; 
	_itoa_s(A, tmp, 2);
		const unsigned int maskA = 65287;
		_itoa_s(maskA, tmp, 2);
		A =(A^maskA);
	_itoa_s(A, tmp, 2);
		cout << tmp <<" ����� � ���������������� ������ (� 4 �� 8 ������������) " <<endl;
}

void v12_2()
{
	setlocale(LC_CTYPE, "ru");
		char tmp[33];
		int A, B, n, p, q, A1;
	    cout << "������� ����� A: ", cin >> A, cout << endl;
	_itoa_s(A, tmp, 2);
		cout << "����� � � �������� �������: " << tmp << endl;
		cout << "������� ���������� ����� � ����� �������, � ������� ����� ������������� ���� � 0 ", cin >> n >> p, cout << endl;
		unsigned int maskA = A;
		for (int i = p - n; i < p; i++) 
		{
			A &= ~(1 << i);
		_itoa_s(A, tmp, 2); 
			cout << "����� A ����� ���������: " << tmp << endl;
		}
		if (A == maskA)
			cout << "����� �� ���������� " << endl;
		A1 = (A ^ maskA) >> (p - n);
	_itoa_s(A1, tmp, 2);
		cout << "����� A1 " << tmp << endl;
	
		cout << "������� ����� B: ", cin >> B, cout << endl;
	_itoa_s(B, tmp, 2);
		cout << "����� B � �������� �������: " << tmp << endl;
		cout << "������� �������, � ������� ����� ������ ���� ", cin >> q, cout << endl;
		A1 = A1 << (q - n);
	_itoa_s(A1, tmp, 2);
		cout << "����� A1:" << tmp << endl;
		unsigned int maskB = ~A1;
		B = (B & maskB) | A1;
	_itoa_s(B, tmp, 2);
		cout << "�������� �����:" << tmp << endl;
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
