#include "vector.hpp"
#include <vector>

int main(void)
{
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "original vector" << std::endl;
		std::cout << std::string(60, '-') << std::endl;
		std::vector<int> v1;
		for (int i = 0; i < 10; i++)
			v1.push_back(i);
		for (std::vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
			std::cout << *iter << std::endl;
	}
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "my own vector" << std::endl;
		std::cout << std::string(60, '-') << std::endl;
		ft::vector<int> v1;
		for (int i = 0; i < 10; i++)
			v1.push_back(i);
		// for (std::vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
		// 	std::cout << *iter << std::endl;
	}
}
