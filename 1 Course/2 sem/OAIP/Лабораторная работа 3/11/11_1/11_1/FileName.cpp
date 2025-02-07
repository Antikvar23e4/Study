
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define LEN 10 //����� ������� �� ������ � ������

int main() {
    setlocale(LC_ALL, "russian");
    FILE* file = NULL;  //���������
    int len = LEN;      //����� ��������� �������
    int ArrOut[LEN] = { 2, 2, 2, 3, 3, 4, 4, 5, 5, 4};

    file = fopen("output.bin", "wb");   //wb - ���� �� ������ ��������� �����

    if (file == NULL) { //���� ������ ������� ��� �������
        printf("Error");
        getchar();
        return 1;
    }
    //���������� ����� ��������� � ������� (��� ��� ������ �����)
    fwrite(&len, sizeof(int), 1, file);
    /* &ArrOut - ������ �� ������, sizeof(int) - ������ ������ ��������,
     * len- ���-�� ��������� �� ������, file - ��������� �� ���� */
    fwrite(ArrOut, sizeof(int), len, file); //������ ������ �������
    printf("������: %d\n", len);
    fclose(file);   //��������� ����
    /***************/
    FILE* Read = fopen("output.bin", "rb"); //rb - ���� �� ������ ��������� �����

    if (Read == NULL) { //���� ������ �������
        printf("Error");
        getchar();
        return 1;
    }
    int lenRead;    //����� ����� ��������� ����� ��������� ��� ������ � �����
    fread(&lenRead, sizeof(int), 1, Read);
    //�������� ������ ��� ������ ��� ������
    int* ArrIn = (int*)malloc(lenRead * sizeof(int));
    //������ ������
    fread(ArrIn, sizeof(int), lenRead, Read);

    fclose(Read);   //��������� ����

    printf("���-�� ��������� ���������: %d \n", lenRead);
    printf("������: ");
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

    free(ArrIn);    //����������� ������
    getchar();
    return 0;
}