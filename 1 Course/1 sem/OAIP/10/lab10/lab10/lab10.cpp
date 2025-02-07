#include <iostream>
using namespace std;

void v1()
{
	setlocale(LC_CTYPE, "Russian");
	using namespace std;
	const int N = 100;
	int i, sz, A[N], rmn = 0, rmx = 99;
	cout << "Ведите длину массива:" << endl;
	cin >> sz;
	srand((unsigned)time(NULL));
	cout << "Элементы начального массива:" << endl;
	for (i = 0; i < sz; i++)
	{
		A[i] = (int)(((double)rand() / (double)RAND_MAX) * (rmx - rmn) + rmn);
	
		cout << A[i]<<" " ;
	}
	cout << "" << endl;
	cout << "Результаты суммы:"  << endl;
	cout << A[0] << " ";
	for (i = 1; i < sz; i++)
	{
		A[i] = A[i - 1] + A[i];
		cout << A[i] << " ";
	}

}
void v2()

{
   setlocale(LC_CTYPE, "Russian");
    using namespace std;
    const int ALPHA = 26;
        char text[100];
        for (int r = 0; r < 100; r++)
        {
            text[r] = '0';
        }
        cout << "Введите текст: " << endl;
        cin.getline(text, 99);
        char letters[ALPHA]; 
        int i = 0;
        cout << "Полученный массив: " << endl;
        for (char n = 'a'; n <= 'z'; n++)
        {
            int count = 0;
            for (int k = 0; k < 100; k++)
            {
                if (text[k] == n)
                    count++;
            }
            if (count == 1)
            {
                letters[i] = n;
                i++;
            }
        }
        for (int e = 0; e < ALPHA; e++)
        {
            cout << letters[e] << " ";
        }
        cout << "" << endl;
  }













int main()
{
	v2();
	v1();
}