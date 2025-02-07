#include <iostream>
using namespace std;

int main()
{
    int arr[60];

    for (int i = 0; i < 50; i++) {
        arr[i] = i;
    }

    int counter = 0;

    for (int i = 1; i < 50; i++) {
        if ((arr[i] % 3 == 0 || arr[i] % 5 == 0) and counter < 6) {
            cout << arr[i] << '\t';
            counter++;
        }
    }
}