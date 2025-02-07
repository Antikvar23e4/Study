
/*Дан файл чисел, содержащий элементы квадратной матрицы (по строкам), причем начальный
элемент файла содержит значение количества столбцов матрицы. Создать новый файл той же структуры,
содержащий транспонированную матрицу.*/

#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Rus");
    FILE* fAptr, * fBptr; //указатели на файлы для считывания и записи
    size_t fSizeOfA;
    long endPos;
    errno_t err;

    err = fopen_s(&fAptr, "A.bin", "wb"); // откроем файл для записи исходных знач
    if (err != 0) {
        perror("ошибка открытия a.bin");
        return;
    }

    cout << "Введите размер матрицы:" << endl; int n; cin >> n;//загоняется  в исходник значения
    fprintf(fAptr, "%d\t", n);
    int* source = new int[n * n];

    for (int g = 0, u = 0; g < n; g++) {
        for (int i = 0; i < n; i++, u++) {
            cout << "Введите " << g + 1 << " " << i + 1 << " элемент массива" << endl;
            cin >> source[u];
            fprintf(fAptr, "%d\t", source[u]);
        }
    }

    delete[] source;

    fclose(fAptr);//закроем файл для открытия в другом режиме
    err = fopen_s(&fAptr, "A.bin", "r"); // открытие файла для считывания данных
    if (err != 0) {
        perror("ошибка открытия a.bin");
        return;
    }

    fseek(fAptr, 0L, SEEK_END); //установка текущей позиции на конец файла

    endPos = ftell(fAptr); //определение размера содержимого файлов

    fseek(fAptr, 0L, SEEK_SET); //установка текущей позииции

    if (!fopen_s(&fBptr, "B.txt", "wb")) { //открытие для перезаписи или создание файла B
        int x;
        fscanf_s(fAptr, "%d", &x);//узнаем размер массива
        int** arr = new int* [x];
        for (int i = 0; i < x; i++)
            arr[i] = new int[x];
        for (int u = 0; u < x; u++) //считывание данных из файлов в массив
            for (int i = 0; i < x; i++) {
                fscanf_s(fAptr, "%d", &(arr[u][i]));
            }

        for (int g = 0; g < x; g++) {
            for (int i = 0; i < x; i++) {
                cout << arr[g][i] << " ";
            }
            cout << endl;
        }
        cout << endl;

        fprintf_s(fBptr, "%d \n", n * n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf_s(fBptr, "%d ", arr[j][i]);
            }
            fprintf_s(fBptr, "\n");
        }
        fclose(fAptr); //закрытие всех файлов
        fclose(fBptr);

        delete[] arr; //освобождение памяти, выделенной для массивов

        cout << "Файл был успешно создан" << std::endl;
    }
    else {
        cout << "Ошибка создания файла" << std::endl;
        return;
    }
    system("pause");
}