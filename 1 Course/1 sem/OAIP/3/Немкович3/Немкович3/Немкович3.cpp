#include <iostream>
void main()
{
	double i=-6, x=4.5, z=4.5e-6, d, f;
	d = tan(-x*i) / sqrt(x-z);
	f = sin(2*d)/d;
	std::cout << "d=" << d << std::endl;
	std::cout << "f=" << f << std::endl;
}

