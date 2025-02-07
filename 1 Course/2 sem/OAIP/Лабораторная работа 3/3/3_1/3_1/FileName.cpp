
/*��� ���� �����, ���������� �������� ���������� ������� (�� �������), ������ ���������
������� ����� �������� �������� ���������� �������� �������. ������� ����� ���� ��� �� ���������,
���������� ����������������� �������.*/

#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_CTYPE, "Rus");
    FILE* fAptr, * fBptr; //��������� �� ����� ��� ���������� � ������
    size_t fSizeOfA;
    long endPos;
    errno_t err;

    err = fopen_s(&fAptr, "A.bin", "wb"); // ������� ���� ��� ������ �������� ����
    if (err != 0) {
        perror("������ �������� a.bin");
        return;
    }

    cout << "������� ������ �������:" << endl; int n; cin >> n;//����������  � �������� ��������
    fprintf(fAptr, "%d\t", n);
    int* source = new int[n * n];

    for (int g = 0, u = 0; g < n; g++) {
        for (int i = 0; i < n; i++, u++) {
            cout << "������� " << g + 1 << " " << i + 1 << " ������� �������" << endl;
            cin >> source[u];
            fprintf(fAptr, "%d\t", source[u]);
        }
    }

    delete[] source;

    fclose(fAptr);//������� ���� ��� �������� � ������ ������
    err = fopen_s(&fAptr, "A.bin", "r"); // �������� ����� ��� ���������� ������
    if (err != 0) {
        perror("������ �������� a.bin");
        return;
    }

    fseek(fAptr, 0L, SEEK_END); //��������� ������� ������� �� ����� �����

    endPos = ftell(fAptr); //����������� ������� ����������� ������

    fseek(fAptr, 0L, SEEK_SET); //��������� ������� ��������

    if (!fopen_s(&fBptr, "B.txt", "wb")) { //�������� ��� ���������� ��� �������� ����� B
        int x;
        fscanf_s(fAptr, "%d", &x);//������ ������ �������
        int** arr = new int* [x];
        for (int i = 0; i < x; i++)
            arr[i] = new int[x];
        for (int u = 0; u < x; u++) //���������� ������ �� ������ � ������
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
        fclose(fAptr); //�������� ���� ������
        fclose(fBptr);

        delete[] arr; //������������ ������, ���������� ��� ��������

        cout << "���� ��� ������� ������" << std::endl;
    }
    else {
        cout << "������ �������� �����" << std::endl;
        return;
    }
    system("pause");
}