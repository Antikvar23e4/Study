
#include <iostream>
#include <algorithm>
// Дан целочисленный массив Х, содержащий n элементов. Найти количество различных чисел среди эле-ментов этого массива.
void v13_1()
{
	setlocale(LC_CTYPE, "Russian");
	using namespace std;
	const int N = 100;
	int i, sz, X[N], rmn = 0, rmx = 25;
	cout << "Ведите длину массива:" << endl;
	cin >> sz;
	srand((unsigned)time(NULL));
	cout << "Элементы  массива:" << endl;
	for (i = 0; i < sz; i++)
	{
		X[i] = (int)(((double)rand() / (double)RAND_MAX) * (rmx - rmn) + rmn);

		cout << X[i] << " ";
	}
	cout << "" << endl;
	int* pX = X;
	int count;          // сколько раз встретилось число
	int result = 0;     // сколько уникальных чисел найдено
	int k;              // счетчик цикла
	for (i = 0; i < N; i++)
	{
		for (count = k = 0; k <= i; k++)  // сколько раз число встречается в массиве до этого момента?
			if (pX[i] == pX[k]) count++;
		if (count == 1)             // если число вcтретилось только 1 раз
		{
			result++;               // увеличиваем число уникальных
		}

	}cout << "" << endl;
		cout << "Количество разных чисел:" << result - 1  << endl;
}


void v13_2() 
{
	setlocale(LC_CTYPE, "Russian");
	using namespace std;
	const int N = 100;
	int i, sz, X[N], rmn = 0, rmx = 25;
	cout << "Ведите длину массива:" << endl;
	cin >> sz;
	srand((unsigned)time(NULL));
	cout << "Элементы  массива:" << endl;
	for (i = 0; i < sz; i++)
	{
		X[i] = (int)(((double)rand() / (double)RAND_MAX) * (rmx - rmn) + rmn);

		cout << X[i] << " ";
	}
	cout << "" << endl;
	int* pX = X;
     int  average, sum = 0, j, tmp;

		for (i = 0; i < sz; i++)
		{
			sum += pX[i];
		}

		average = sum / sz;
		printf("\n\naverage: %d\n\n", average);
		for (i = 0; i < sz; i++)
		{
			if (pX[i] >= average && i)
			{
				tmp = pX[i];
				for (j = i; pX[j - 1] < average && j; j--)
					pX[j] = pX[j - 1];
				pX[j] = tmp;
			}
		}

		for (i = 0; i < sz; i++)
			printf("%d ", pX[i]);
		putchar('\n');
}


void v11_1()
{
		setlocale(LC_ALL, "Russian");
		using namespace std;
		int n = 0, min;
		int count = 0;
		cout << "Введите количество чисел в последовательности: " << endl;
		cin >> n;
		int* pArr = new int[n];
		cout << "Введите последовательность из " << n << " натуральных чисел " << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "[" << i << "] = ";
			cin >> pArr[i];

		}
		sort(pArr, pArr + n);
		for (int i = 0; i < n; ++i)
			if (pArr[i] != i + 1)
			{
				cout << "Минимальное число, отсутсвующее в последовательности:" << i + 1 << endl;
				break;
			}
}


void v11_2()
{
	setlocale(LC_ALL, "Russian");
	using namespace std;
	int t, s1(0), s2(0), n, m;
	cout << "Введите значение t: " << "t="; cin >> t;
	cout << "Введите количетво элементов в массиве A: " << endl;
	cin >> n;
	cout << "Введите количество элементов в массиве В: " << endl;
	cin >> m;
	int* a = new int[n];
	int* b = new int[m];
	cout << "Введите элементы массива А \n";
	for (int i = 0; i < n; i++)
	{
		cout << "a[" << i << "]="; cin >> a[i];
	}
	cout << "Введите элементы массива B \n";
	for (int i = 0; i < m; i++)
	{
		cout << "b[" << i << "]="; cin >> b[i];
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] < t) s1++;
	}
	for (int i = 0; i < m; i++)
	{
		if (b[i] < t) s2++;
	}
	cout << "В массиве A '" << s1 << "' элемента(ов) меньше " << t << "\n";
	cout << "В массиве B '" << s2 << "' элемента(ов) меньше " << t << "\n";
	if (s1 < s2)
	{
		for (int i = 0; i < m; i++)
			cout << b[i] << " ";
		cout << endl;
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	else {
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
		for (int i = 0; i < m; i++)
			cout << b[i] << " ";
		cout << endl;
	}
	
}





void v10_1()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	const int maxSize = 10;
	int n = 10, i, a[maxSize], b[maxSize], min, j;
	srand((unsigned)time(NULL));
	cout << "A:" << endl;
	for (i = 0; i < n; i++) 
	{
		*(a + i) = rand() % 99;
		cout << *(a + i) << " ";
	}
	cout << endl;
	cout << "B:" << endl;
	for (i = 0; i < n; i++) 
	{
		*(b + i) = rand() % 99;
		cout << *(b + i) << " ";
	}
	cout << endl;
	min = a[0]; 
	for (i = 0; i < n; i++) {  
		for (j = 0; j < n; j++) {
			if (*(a + i) < min && *(a + i) != *(b + j)) {
				min = *(a + i);
			}
			else;
		}
	}
	cout << "Минимальное значение - " << min << endl; 
	system("pause");
}

void v10_2() {
	setlocale(LC_ALL, "Russian");
	using namespace std;
	const int N = 100;
	int A[N]{}, B[N]{}, n = 6, C[N]{};

	cout << "\nМассив A: \n" << endl;

	for (int i = 0; i < n; i++) {
		*(A + i) = rand() % 99;
		cout << "A[" << i << "]: адрес = " << A + i << "\tзначение = " << *(A + i) << endl;
	}

	cout << "\nМассив B: \n" << endl;

	for (int i = 0; i < n; i++) {
		*(B + i) = rand() % 99;
		cout << "B[" << i << "]: адрес = " << B + i << "\tзначение = " << *(B + i) << endl;
	}

	cout << "\nМассив C: \n" << endl;

	for (int i = 0; i < n; i++) {
		*(C + i) = *(A + i) + *(B + i);
		cout << "C[" << i << "]:  значение = " << *(C + i) << endl;
	}
}

void v3_1()
{
	setlocale(LC_ALL, "rus");
	using namespace std;
	const int maxSize = 10;
	int n = 10, i, a[maxSize], b[maxSize], min, k = 0, j = 0, t;
	cout << "Введите число t = ";
	cin >> t;
	cout << endl;
	srand((unsigned)time(NULL));
	cout << "A:" << endl;
	for (i = 0; i < n; i++) 
	{
		*(a + i) = rand() % 5;
		cout << *(a + i) << " ";
	}
	cout << endl;
	cout << "B:" << endl;
	for (i = 0; i < n; i++) 
	{
		*(b + i) = rand() % 5;
		cout << *(b + i) << " ";
	}
	cout << endl;
	for (i = 0; i < n; i++) { 
		if (*(a + i) < t) {
			k = k + 1;

		}
	}
	for (i = 0; i < n; i++) { 
		if (*(b + i) < t) {
			j = j + 1;

		}
	}
	cout << "Выводим нужный массив:" << endl; 
	if (k > j) {
		for (i = 0; i < n; i++) {
			cout << *(a + i) << " ";
		}
		cout << endl;
	}

	else {
		for (i = 0; i < n; i++) {
			cout << *(b + i) << " ";
		}
		cout << endl;

	}
	if (k == j) {  
		cout << "Число чисел меньше t одинаково!";
		cout << endl;
		}
	
}


void v3_2() 
{

	setlocale(LC_ALL, "rus");
	using namespace std;
	const int maxSize = 10;
	int m = 10, i, c[maxSize], d[maxSize], min, k = 0, j = 0, v = 0;
	srand((unsigned)time(NULL));
	cout << "C:" << endl;
	for (i = 0; i < m; i++) 
	{
		*(c + i) = rand() % 5;
		cout << *(c + i) << " ";
	}
	cout << endl;
	cout << "D:" << endl;
	for (i = 0; i < m; i++) 
	{
		*(d + i) = rand() % 5;
		cout << *(d + i) << " ";
	}
	cout << endl; 
	for (i = 0; i < m; i++) {
		if (*(c + i) == *(d + i)) {
			k = k + 1;

		}
	}
	for (i = 0; i < m; i++) {
		if (*(c + i) > *(d + i)) {
			j = j + 1;

		}
	}
	for (i = 0; i < m; i++) {
		if (*(c + i) < *(d + i)) {
			v = v + 1;

		}
	}
	cout << "k1 = " << k << endl;
	cout << "k2 = " << j << endl;
	cout << "k3 = " << v << endl;
	cout << endl;
}














int main() 
{
	v3_1();
	v3_2();
	v10_1();
	v10_2();
	v11_1();
	v11_2();
	v13_2();
	v13_1();
	
}


