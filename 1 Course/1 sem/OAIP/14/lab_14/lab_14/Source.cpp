#include <iostream>
using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    srand((unsigned int)time(0));
    const int rows = 5, cols = 6;
    int A[rows][cols]{};
    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0, kolich = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = rand() % 200;
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < rows; i++) {
        sum1 += A[i][0];
        sum2 += A[i][1];
        sum3 += A[i][2];
        sum4 += A[i][3];
        sum5 += A[i][4];
        sum6 += A[i][5];
    }
    for (int i = 0; i < rows; i++) {
        if (A[i][0] > (sum1 - A[i][0])) {
            kolich++;
        }
        if (A[i][1] > (sum2 - A[i][1])) {
            kolich++;
        }
        if (A[i][2] > (sum3 - A[i][2])) {
            kolich++;
        }
        if (A[i][3] > (sum4 - A[i][3])) {
            kolich++;
        }
        if (A[i][4] > (sum5 - A[i][4])) {
            kolich++;
        }
        if (A[i][5] > (sum6 - A[i][5])) {
            kolich++;
        }
    }
    cout << "Количество элементов матрицы, значение каждого из которых больше суммы остальных элементов своего столбца равно " << kolich << endl;
}


#include <iostream>
void main()
{
    setlocale(LC_CTYPE, "Russian");
    using namespace std;
    const int n = 4, m = 4;
    int B[n][m];
    int i, j, row = 0, column = 0;
    cout << "Введите элементы массива" << endl;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            cin >> B[i][j];
    int min = B[0][0];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (min > B[i][j])
            {
                min = B[i][j];
                column = i;
                row = j;
            }
    cout << " Исходный массив:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\n";
        for (int j = 0; j < m; j++)
            cout << "B[" << i << "," << j << "] =" << B[i][j] << "\t";
    }
    cout << "\nСтолбец с минимальным элементом: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "\n";

        cout << "B[" << i << "," << row << "] =" << B[i][row] << "\t";
    }
    cout << endl;
    cout << endl;
    cout << "Минимальный элемент B[" << column << "," << row << "] =" << min << endl;
}





