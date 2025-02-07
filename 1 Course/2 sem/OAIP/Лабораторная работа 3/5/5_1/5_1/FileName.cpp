 //Даны два файла целых чисел, содержащие элементы квадратных матриц с именами A и B по строкам, причем начальный элемент каждого файла содержит количество столбцов
//соответствующей матрицы.Создать файл той же структуры с именем C, содержащий произведение матриц А и В.

#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Rus");
    FILE* fAptr, * fBptr, * fCptr; //указатели на файлы для считывания и записи
    size_t fSizeOfA;
    size_t fSizeOfB;
    long endPos;
    long endPosB;
    errno_t err;
    //1
    err = fopen_s(&fAptr, "A.txt", "wb"); // откроем файл для записи исходных знач
    if (err != 0) {
        perror("ошибка открытия a.txt");
        return;
    }


    cout << "Введите размер матриц:\n"; int n; cin >> n;//загоняется  в исходник значения
    fprintf(fAptr, "%d\n", n);
    int* source = new int[n * n];

    int x = n;
    int** arrB = new int* [x];
    for (int i = 0; i < x; i++)
        arrB[i] = new int[x];

    int** arr = new int* [x];
    for (int i = 0; i < x; i++)
        arr[i] = new int[x];

    int** arrA = new int* [x];
    for (int i = 0; i < x; i++)
        arrA[i] = new int[x];

    for (int g = 0, u = 0; g < n; g++) {
        for (int i = 0; i < n; i++, u++) {
            source[u] = rand() % 10;
            fprintf(fAptr, "%d ", source[u]);
            printf("%d ", source[u]);
        }
        fprintf(fAptr, "\n");
        printf("\n");
    }

    delete[] source;

    fclose(fAptr);//закроем файл для открытия в другом режиме
    err = fopen_s(&fAptr, "A.txt", "r"); // открытие файла для считывания данных
    if (err != 0) {
        perror("ошибка открытия a.txt");
        return;
    }

    fseek(fAptr, 0L, SEEK_END); //установка текущей позиции на конец файла

    endPos = ftell(fAptr); //определение размера содержимого файлов

    fseek(fAptr, 0L, SEEK_SET); //установка текущей позииции

    //2
    //-------------------------------------------------------------
    err = fopen_s(&fBptr, "B.txt", "wb"); // откроем файл для записи исходных знач
    if (err != 0) {
        perror("ошибка открытия a.txt");
        return;
    }

    fprintf(fBptr, "%d\n", n);
    int* sourceB = new int[n * n];
    printf("\n");
    printf("\n");
    for (int g = 0, u = 0; g < n; g++) {
        for (int i = 0; i < n; i++, u++) {
            sourceB[u] = rand() % 10;
            fprintf(fBptr, "%d ", sourceB[u]);
            printf("%d ", sourceB[u]);
        }
        fprintf(fBptr, "\n");
        printf("\n");
    }

    delete[] sourceB;

    fclose(fBptr);//закроем файл для открытия в другом режиме
    err = fopen_s(&fBptr, "B.txt", "r"); // открытие файла для считывания данных
    if (err != 0) {
        perror("ошибка открытия B.txt");
        return;
    }

    fseek(fBptr, 0L, SEEK_END); //установка текущей позиции на конец файла

    endPosB = ftell(fBptr); //определение размера содержимого файлов

    fseek(fBptr, 0L, SEEK_SET); //установка текущей позииции
    //---------------------------------------------------------------------
    printf("\n\nПроизведение массивов:\n\n");
    if (!fopen_s(&fCptr, "C.txt", "wb")) { //открытие для перезаписи или создание файла B
        int a;
        int b;
        fscanf_s(fAptr, "%d", &a);//узнаем размер массива
        fscanf_s(fBptr, "%d", &b);


        for (int u = 0; u < x; u++) //считывание данных из файлов в массив
            for (int i = 0; i < x; i++) {
                fscanf_s(fAptr, "%d", &(arrA[u][i]));

            }

        for (int u = 0; u < x; u++)
            for (int i = 0; i < x; i++) {
                fscanf_s(fBptr, "%d", &(arrB[u][i]));
            }

        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < x; j++)
            {
                arr[i][j] = 0;
                for (int k = 0; k < x; k++)
                    arr[i][j] += arrA[i][k] * arrB[k][j];
            }
        }
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < x; j++)
            {
                fprintf(fCptr, "%d ", arr[i][j]);
                printf("%d ", arr[i][j]);
            }
            fprintf(fCptr, "\n");
            printf("\n");
        }


        fclose(fAptr); //закрытие всех файлов
        fclose(fBptr);
        fclose(fCptr);
        delete[] arr; //освобождение памяти, выделенной для массивов
        delete[] arrA;
        delete[] arrB;
        cout << "Файл был успешно создан" << std::endl;
    }
    else {
        cout << "Ошибка создания файла" << std::endl;
        return;
    }
    system("pause");
}



