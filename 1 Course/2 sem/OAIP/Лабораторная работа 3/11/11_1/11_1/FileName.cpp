
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define LEN 10 //длина массива на запись и чтение

int main() {
    setlocale(LC_ALL, "russian");
    FILE* file = NULL;  //указатель
    int len = LEN;      //число элементов массива
    int ArrOut[LEN] = { 2, 2, 2, 3, 3, 4, 4, 5, 5, 4};

    file = fopen("output.bin", "wb");   //wb - флаг на запись бинарного файла

    if (file == NULL) { //если нельзя создать или открыть
        printf("Error");
        getchar();
        return 1;
    }
    //записываем число элементов в массиве (для его чтения далее)
    fwrite(&len, sizeof(int), 1, file);
    /* &ArrOut - ссылка на массив, sizeof(int) - размер одного элемента,
     * len- кол-во элементов на запись, file - указатель на файл */
    fwrite(ArrOut, sizeof(int), len, file); //запись самого массива
    printf("Запись: %d\n", len);
    fclose(file);   //закрываем файл
    /***************/
    FILE* Read = fopen("output.bin", "rb"); //rb - флаг на чтение бинарного файла

    if (Read == NULL) { //если нельзя открыть
        printf("Error");
        getchar();
        return 1;
    }
    int lenRead;    //здесь будет храниться число элементов для чтения в файле
    fread(&lenRead, sizeof(int), 1, Read);
    //выделяем память под массив для чтения
    int* ArrIn = (int*)malloc(lenRead * sizeof(int));
    //читаем данные
    fread(ArrIn, sizeof(int), lenRead, Read);

    fclose(Read);   //закрываем файл

    printf("Кол-во элементов прочитано: %d \n", lenRead);
    printf("Массив: ");
    for (int i = 0; i < lenRead - 1; i++)
        for (int j = i + 1; j < lenRead; j++)
            if (ArrIn[i] == ArrIn[j])
            {
                for (int k = j; k < lenRead; k++)
                    ArrIn[k] = ArrIn[k + 1];
                lenRead--;
                j--;
            }
    //for (int i = 0; i < lenRead; i++)
    for (int i = 0; i < lenRead; i++)
        printf("%d ", ArrIn[i]);

    free(ArrIn);    //освобождаем память
    getchar();
    return 0;
}