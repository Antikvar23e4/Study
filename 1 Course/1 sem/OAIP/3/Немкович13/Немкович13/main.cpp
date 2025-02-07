#include <iostream>
void main()
{
	double y, w, m = 6, z = 0.05e-5;
	y = cos(5 * m) / sin(sin(0.4 * m));
	w = 4 * z * y - 7 * exp(-2 * y);
	std::cout << "y=" << y << std::endl;
	std::cout << "w=" << w << std::endl;
}
