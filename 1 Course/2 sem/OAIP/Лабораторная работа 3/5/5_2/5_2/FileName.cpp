// Создать текстовый файл F1 не менее, чем из 6 строк, и записать в него информацию.
//Скопировать в файл F2 только те строки из F1, которые начинаются с буквы «А». 

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
	printf("Сколлько строк выв хотите ввести? ");
	int n;
	cin >> n;
	fopen_s(&mf, "tst.txt", "w");
	printf("Введите текст \n");
	cin.ignore(50, '\n');
	for (int i = 0; i < n; i++)
	{
		cin.getline(str, 50);
		fputs(str, mf); fputs("\n", mf);
	}
	fclose(mf);


	fopen_s(&af, "output.txt", "w");
	err = fopen_s(&mf, "tst.txt", "r");  //Открытие для чтения

	if (err != NULL)                 //Проверка открытия файла
	{
		printf("Ошибка открытия файла\n"); return -1;
	}
	else
	{
		printf("\nСчитаны строки:\n");
		estr = fgets(str, sizeof(str), mf);
		char ch[2] = "A";
		while (estr != NULL)
		{
			if (str[0] == ch[0])
			{
				fputs(str, af); fputs("\n", af);
			}
			puts(str);
			estr = fgets(str, sizeof(str), mf); //Чтение строки файла 

		}
	}

	if (fclose(mf) == EOF)
		printf("Ошибка закрытия\n");
	if (fclose(af) == EOF)
		printf("Ошибка закрытия\n");
	return 0;
}
