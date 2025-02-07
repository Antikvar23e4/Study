// По заданному числу n определить символ, который стоит на n-ом месте последовательности, получившейся после шага c номером 26.
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
    cout << "Введите число "; cin >> n;
    char symbol = poisk(n);
    cout << "Символ на позиции " << n << " после шага 26: " << symbol << endl;
    return 0;
}