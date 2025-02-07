//Разработать программу, реализующую рекурсивную функцию подсчета количества всех положительных делителей натурального числа n.
#include <iostream>
using namespace std;

int deliteli(int n, int i = 1, int count = 0) {
    if (i > n) {
        return count;
    }
    if (n % i == 0) {
        count++;
    }
    return deliteli(n, i + 1, count);
}

int main() {
    setlocale(LC_CTYPE, "rus");
    int n;
    cout << "Введите натуральное число: ";
    cin >> n;
    int count = deliteli(n);
    cout << "Количество положительных делителей " << n << " : " << count << endl;
    return 0;
}
