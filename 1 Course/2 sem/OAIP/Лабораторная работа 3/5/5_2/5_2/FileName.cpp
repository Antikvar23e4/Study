// ������� ��������� ���� F1 �� �����, ��� �� 6 �����, � �������� � ���� ����������.
//����������� � ���� F2 ������ �� ������ �� F1, ������� ���������� � ����� ���. 

#include <iostream>
#include <stdio.h>  
#include <string>
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	FILE* mf;
	FILE* af; char str[50];   errno_t err;
	char* estr;
	printf("�������� ����� ��� ������ ������? ");
	int n;
	cin >> n;
	fopen_s(&mf, "tst.txt", "w");
	printf("������� ����� \n");
	cin.ignore(50, '\n');
	for (int i = 0; i < n; i++)
	{
		cin.getline(str, 50);
		fputs(str, mf); fputs("\n", mf);
	}
	fclose(mf);


	fopen_s(&af, "output.txt", "w");
	err = fopen_s(&mf, "tst.txt", "r");  //�������� ��� ������

	if (err != NULL)                 //�������� �������� �����
	{
		printf("������ �������� �����\n"); return -1;
	}
	else
	{
		printf("\n������� ������:\n");
		estr = fgets(str, sizeof(str), mf);
		char ch[2] = "A";
		while (estr != NULL)
		{
			if (str[0] == ch[0])
			{
				fputs(str, af); fputs("\n", af);
			}
			puts(str);
			estr = fgets(str, sizeof(str), mf); //������ ������ ����� 

		}
	}

	if (fclose(mf) == EOF)
		printf("������ ��������\n");
	if (fclose(af) == EOF)
		printf("������ ��������\n");
	return 0;
}
