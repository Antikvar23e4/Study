#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int main(int argc, char* argv[])
{
	std::vector<std::string> arr;
	std::string str;
	std::string word;
	int i = 0;

	std::cout << "Enter string.." << std::endl;
	std::getline(std::cin, str);

	std::stringstream  data(str);

	while (std::getline(data, word, ' '))
	{
		if (i++ % 2 == 0)
		{
			arr.push_back(word);
		}
	}

	for (std::vector<std::string>::iterator iter = arr.begin(); iter < arr.end(); ++iter)
		std::cout << *iter << " ";

	return 0;
}