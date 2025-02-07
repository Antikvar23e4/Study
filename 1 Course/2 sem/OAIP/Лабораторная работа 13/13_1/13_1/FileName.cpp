#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
// Ввести массивы А и В. В массив С перенести элементы массива А с нечетным значением и элементы массива В с четным значением.
// Массив С отсортировать по возрастанию, используя алгоритмы сортировок: сортировка Шелла, сортировка Хоара.
using namespace std;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Функция для переноса элементов из массивов А и В в массив С
void transferElements(int A[], int sizeA, int B[], int sizeB, int C[], int& sizeC) {
    for (int i = 0; i < sizeA; i++) {
        if (A[i] % 2 != 0) {
            C[sizeC] = A[i];
            sizeC++;
        }
    }
    for (int i = 0; i < sizeB; i++) {
        if (B[i] % 2 == 0) {
            C[sizeC] = B[i];
            sizeC++;
        }
    }
}

// Функция для сортировки массива методом сортировки Шелла
void shellSort(int arr[], int size) {
    int gap, i, j, temp;
    for (gap = size / 2; gap > 0; gap /= 2) {
        for (i = gap; i < size; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Функция для сортировки массива методом сортировки Хоара
void hoarSort(int arr[], int left, int right) {
    int i = left, j = right, tmp;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j) {
        hoarSort(arr, left, j);
    }
    if (i < right) {
        hoarSort(arr, i, right);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    const int N = 10;
    int A[N], B[N], C[N], count = 0;
    const int sizeA = 10;
    const int sizeB = 10;
    int Cc[sizeA + sizeB];
    int sizeC = 0;
    for (;;) {
        int vibor;
        cout << endl << endl;
        cout << "1. Вариант 11\n"
            << "2. Варинт 5\n"
            << "3. Вариант 10\n"
            << "0. Выход\n";
        cout << "? ";
        cin >> vibor;
        cout << endl << endl;
        switch (vibor) {
        case 1: {
            // Заполнение массивов A и B случайными числами
            cout << "Ввести массивы А и В. В массив С перенести элементы массива А с нечетным значением и элементы массива В с четным значением.";
            cout << "Массив С отсортировать по возрастанию, используя алгоритмы сортировок : сортировка Шелла, сортировка Хоара." << endl;
            srand(time(NULL));
            fillArray(A, sizeA);
            fillArray(B, sizeB);

            cout << "Массив A:" << endl;
            printArray(A, sizeA);
            cout << "Массив B:" << endl;
            printArray(B, sizeB);

            transferElements(A, sizeA, B, sizeB, Cc, sizeC);

            cout << "Массив C:" << endl;
            printArray(Cc, sizeC);

            // Замер времени
            auto start = chrono::high_resolution_clock::now();
            shellSort(Cc, sizeC);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            cout << "Массив С после сортировки Шелла:" << endl;
            printArray(Cc, sizeC);
            cout << "Время выполнения сортировки: " << duration.count() << " мс" << endl;


            hoarSort(Cc, 0, sizeC - 1);
            cout << "Массив С после сортировки Хоара:" << endl;
            printArray(Cc, sizeC);
            break;
        }

        case 2: {
            cout << "Ввести массивы А и В. В массив С перенести элементы массива А с четным значением и элементы массива В с нечетным значением. ";
            cout << "Массив С отсортировать по возрастанию, используя алгоритмы сортировок: «пузырек», сортировка выбором." << endl;
            for (int i = 0; i < N; i++) {
                A[i] = rand() % 100;
                B[i] = rand() % 100;
            }
            cout << "Массив A: ";
            printArray(A, N);
            cout << "Массив B: ";
            printArray(B, N);
            int cSize = 0;
            for (int i = 0; i < N; i++) {
                if (A[i] % 2 == 0) {
                    C[cSize++] = A[i];
                }
                if (B[i] % 2 != 0) {
                    C[cSize++] = B[i];
                }
            }

            cout << "Массив С перед сортировой: ";
            printArray(C, cSize);
            bubbleSort(C, cSize);
            cout << "Массив С после сортировки 'пузырёк': ";
            printArray(C, cSize);
            selectionSort(C, cSize);
            cout << "Массив С после сортировки выбором: ";
            printArray(C, cSize);
            break;
        }
        case 3: {

            cout << "Ввести массивы А и В. В массив С перенести те элементы массива А, которые больше максимального элемента массива В. ";
            cout << "Массив С отсортировать по убыванию, используя алгоритмы сортировок: «пузырек», в сортировка простой вставкой." << endl;
            for (int i = 0; i < N; i++) {
                A[i] = rand() % 100;
                B[i] = rand() % 100;
            }
            cout << "Массив A: ";
            printArray(A, N);
            cout << "Массив B: ";
            printArray(B, N);
            int maxB = *max_element(B, B + N);
            int cSize = 0;
            for (int i = 0; i < N; i++) {
                if (A[i] > maxB) {
                    C[cSize++] = A[i];
                }
            }
            cout << "Массив С перед сортировой: ";
            printArray(C, cSize);
            bubbleSort(C, cSize);
            cout << "Массив С после сортировки 'пузырёк': ";
            printArray(C, cSize);
            insertionSort(C, cSize);
            cout << "Массив С после сортировки выбором: ";
            printArray(C, cSize);
            break;
        }
        case 0: {
            return 0;
            break;
        }
        }
    }
}