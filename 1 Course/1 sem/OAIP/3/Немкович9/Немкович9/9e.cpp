#include <iostream>
void main()
{
	double y = 0.5, c = 1.4, x = 2e-4, z, u;
	z = exp(c*x)/y+3;
	u = sqrt(pow(z,3)-0.1);
	
	std::cout << "u=" << u << std::endl;
	std::cout << "z=" << z << std::endl;
}
