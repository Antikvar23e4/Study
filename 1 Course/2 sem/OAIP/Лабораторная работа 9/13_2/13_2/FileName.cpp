//����������� ���������, ����������� ����������� �������� ���������� �������� S(x) ��� ����� ����� �� ������������� ��� - ����� x.
#include <iostream>
using namespace std;

int functionS(int x) {
    if (x > 100) {
        return x + 10;
    }
    else {
        return functionS(functionS(x + 4));
    }
}

int main() {
    setlocale(LC_CTYPE, "rus");
    int x;
    cout << "������� ����� ����� ��������������� ��������: ";
    cin >> x;
    int result = functionS(x);
    cout << "S(" << x << ") = " << result << endl;
    return 0;
}