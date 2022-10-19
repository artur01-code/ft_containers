#include "vector.hpp"
#include <vector>

void print_varray(ft::vector<int> &rhs)
{
	std::cout << rhs << std::endl;
}

int main(void)
{
	//		THE ORIGINAL VECTOR CLASS
	// {
	// 	std::cout << std::string(60, '-') << std::endl;
	// 	std::cout << "original vector" << std::endl;
	// 	std::cout << std::string(60, '-') << std::endl;
	// 	std::vector<int> v1;
	// 	for (int i = 0; i < 10; i++)
	// 		v1.push_back(i);
	// 	for (std::vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
	// 		std::cout << *iter << " ";
	// 	std::cout << " | | " << std::endl;
	// }
	//		TESTING MY OWN VECTOR CLASS
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "my own vector" << std::endl;
		std::cout << std::string(60, '-') << std::endl;
		ft::vector<int> v1;
		for (int i = 0; i < 5; i++)
			v1.push_back(i);
		ft::vector<int> v2;
		v2 = v1; // test the copy assigment operator
		ft::vector<int> v3(v1); //test copy constructor

		print_varray(v1);
		print_varray(v2);
		print_varray(v3);

	}
}
