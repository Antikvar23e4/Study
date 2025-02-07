#include <iostream>
#include <cmath>
using namespace std;

void v1()
{
setlocale(LC_CTYPE, "ru");
	float a,b,n,s,h,x;
	cout << "¬ведите a: "<<endl;
	cin >> a;
	cout << "¬ведите b: " << endl;
	cin >> b;
	cout << "¬ведите n: " << endl;
	cin >> n;
	h = (b - a) / n;
	cout << "¬ысота равна: " << h << endl;
	x = a; 
	s = 0;
	while (x < (b - h)) {
		s += h * ((2 + pow(x, 3)) + (2 + pow(x + h, 3))) / 2;
		x += h;
	}
	cout << "ѕлощадь равна: " << s << endl;
}


void v2()
{
	setlocale(LC_CTYPE, "ru");
	float a , b , n , s1 = 0, i = 1, h, x, z, s2 = 0;
	cout << "¬ведите a: " << endl;
	cin >> a;
	cout << "¬ведите b: " << endl;
	cin >> b;
	cout << "¬ведите n: " << endl;
	cin >> n;
	h = (b - a) / (2 * n);
	x = a + 2 * h;

	while (i < n)
	{
		s2 += (2 + pow(x, 3));
		x += h;
		s1 += (2 + pow(x, 3));
		x += h;
		i++;
	}

	z = (h / 3) * (2 + pow(a, 3) + 4 * (2 + pow(a + h, 3)) + 4 * s1 + 2 * s2 + 2 + pow(b, 3));
	 cout << "ѕлощадь равна: " << z << endl;

}

void v3()
{
setlocale(LC_CTYPE, "Russian");
float a, b, e, x;
cout << "¬ведите a" << endl;
cin >> a;
cout << " " << endl;
cout << "¬ведите b" << endl;
cin >> b;
cout << " " << endl;
cout << "¬ведите e" << endl;
cin >> e;
cout << " " << endl;
while (abs(a - b) > 2 * e) {
	x = (a + b) / 2;
	if ((exp(x) + x - 4) * (exp(a) + a - 4) <= 0) {
		b = x;
	}
	else {
		a = x;
	}
}
cout << "x = " << x << endl << endl;
} 



int main()
{ 
v1();
v2();
v3();
return 0;


}

