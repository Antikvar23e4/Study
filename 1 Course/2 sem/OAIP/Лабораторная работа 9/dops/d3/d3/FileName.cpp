// �� ��������� ����� n ���������� ������, ������� ����� �� n-�� ����� ������������������, ������������ ����� ���� c ������� 26.
#include <iostream>
using namespace std;

char poisk(int n) {
    string s = "abcdefghijklmnopqrstuvwxyz"; 
    if (n <= 26) {
        return s[n - 1]; 
    }
    else {
        return s[n - 26 - 1]; 
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    int n;
    cout << "������� ����� "; cin >> n;
    char symbol = poisk(n);
    cout << "������ �� ������� " << n << " ����� ���� 26: " << symbol << endl;
    return 0;
}