#include <iostream>
#include <ctime>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    clock_t start = clock();  
    int iteration_count = 0;  
    bool flag5 = true, flag10 = true;//флаги чтобы повторно не выводились значения

    while (true) {
        iteration_count++;  

        if (flag5 && (clock() - start) / CLOCKS_PER_SEC == 5 ) {
            cout << "Число итераций через 5с: " << iteration_count << '\n';
            flag5 = false;  
        }
        if (flag10 && (clock() - start) / CLOCKS_PER_SEC == 10) {
            cout << "Число итераций через 10с: " << iteration_count << '\n';
            flag10 = false;  
        }
        if ((clock() - start) / CLOCKS_PER_SEC == 15) {
            cout << "Число итераций через 15с: " << iteration_count << '\n';
            break;  
        }
    }
    cout << "Итоговое количество итераций: " << iteration_count << endl;
    return 0;
}
