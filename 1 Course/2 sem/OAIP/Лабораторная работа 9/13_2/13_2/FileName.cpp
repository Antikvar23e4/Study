//Разработать программу, реализующую рекурсивный алгоритм вычисления значений S(x) для любых целых не отрицательных зна - чений x.
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
    cout << "Введите любое целое неотрицательное значение: ";
    cin >> x;
    int result = functionS(x);
    cout << "S(" << x << ") = " << result << endl;
    return 0;
}