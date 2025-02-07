 //���� ��� ����� ����� �����, ���������� �������� ���������� ������ � ������� A � B �� �������, ������ ��������� ������� ������� ����� �������� ���������� ��������
//��������������� �������.������� ���� ��� �� ��������� � ������ C, ���������� ������������ ������ � � �.

#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Rus");
    FILE* fAptr, * fBptr, * fCptr; //��������� �� ����� ��� ���������� � ������
    size_t fSizeOfA;
    size_t fSizeOfB;
    long endPos;
    long endPosB;
    errno_t err;
    //1
    err = fopen_s(&fAptr, "A.txt", "wb"); // ������� ���� ��� ������ �������� ����
    if (err != 0) {
        perror("������ �������� a.txt");
        return;
    }


    cout << "������� ������ ������:\n"; int n; cin >> n;//����������  � �������� ��������
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

    fclose(fAptr);//������� ���� ��� �������� � ������ ������
    err = fopen_s(&fAptr, "A.txt", "r"); // �������� ����� ��� ���������� ������
    if (err != 0) {
        perror("������ �������� a.txt");
        return;
    }

    fseek(fAptr, 0L, SEEK_END); //��������� ������� ������� �� ����� �����

    endPos = ftell(fAptr); //����������� ������� ����������� ������

    fseek(fAptr, 0L, SEEK_SET); //��������� ������� ��������

    //2
    //-------------------------------------------------------------
    err = fopen_s(&fBptr, "B.txt", "wb"); // ������� ���� ��� ������ �������� ����
    if (err != 0) {
        perror("������ �������� a.txt");
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

    fclose(fBptr);//������� ���� ��� �������� � ������ ������
    err = fopen_s(&fBptr, "B.txt", "r"); // �������� ����� ��� ���������� ������
    if (err != 0) {
        perror("������ �������� B.txt");
        return;
    }

    fseek(fBptr, 0L, SEEK_END); //��������� ������� ������� �� ����� �����

    endPosB = ftell(fBptr); //����������� ������� ����������� ������

    fseek(fBptr, 0L, SEEK_SET); //��������� ������� ��������
    //---------------------------------------------------------------------
    printf("\n\n������������ ��������:\n\n");
    if (!fopen_s(&fCptr, "C.txt", "wb")) { //�������� ��� ���������� ��� �������� ����� B
        int a;
        int b;
        fscanf_s(fAptr, "%d", &a);//������ ������ �������
        fscanf_s(fBptr, "%d", &b);


        for (int u = 0; u < x; u++) //���������� ������ �� ������ � ������
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


        fclose(fAptr); //�������� ���� ������
        fclose(fBptr);
        fclose(fCptr);
        delete[] arr; //������������ ������, ���������� ��� ��������
        delete[] arrA;
        delete[] arrB;
        cout << "���� ��� ������� ������" << std::endl;
    }
    else {
        cout << "������ �������� �����" << std::endl;
        return;
    }
    system("pause");
}



