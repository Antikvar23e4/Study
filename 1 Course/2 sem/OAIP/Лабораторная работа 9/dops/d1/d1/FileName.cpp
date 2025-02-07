//ƒано n различных натуральных чисел (n = 5). Ќапечатать все перестановки этих чисел.
#include <iostream>
#include <algorithm>
using namespace std;

void perestanovka(int* arr, int start, int end) {
    if (start == end) { 
        for (int i = 0; i <= end; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else { 
        for (int i = start; i <= end; i++) {
            swap(arr[start], arr[i]); 
            perestanovka(arr, start + 1, end);
            swap(arr[start], arr[i]); 
        }
    }
}

int main() {
    int arr[] = { 5, 8, 2, 5, 9 };
    int n = sizeof(arr) / sizeof(int);
    sort(arr, arr + n); 
    perestanovka(arr, 0, n - 1);
    return 0;
}