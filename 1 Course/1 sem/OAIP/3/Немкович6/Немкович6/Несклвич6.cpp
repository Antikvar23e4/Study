#include <iostream>
void main()
{
	double y = 0.956, a = 5e-6, n = 4, t, u, s;
	t = 1 / sqrt(y) + 14 * a;
	u = sin(t + 1) / (a + 2);
	s = log((2*n / 3) + 10-n / u);
	std::cout << "t=" << t << std::endl;
	std::cout << "u=" << u << std::endl;
	std::cout << "s=" << s << std::endl;
}


