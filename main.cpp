#include "vector.hpp"
#include <vector>

void print_varray(ft::vector<int> &rhs)
{
	std::cout << rhs << std::endl;
}

int main(void)
{
	//		THE ORIGINAL VECTOR CLASS
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "original vector" << std::endl;
		std::cout << std::string(60, '-') << std::endl;
		std::vector<int> v1;
		for (int i = 0; i < 10; i++)
			v1.push_back(i);
		for (std::vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
			std::cout << *iter << " ";
		std::cout << " | | " << std::endl;
	}
	//		TESTING MY OWN VECTOR CLASS
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "my own vector" << std::endl;
		std::cout << std::string(60, '-') << std::endl;
		ft::vector<int> v1;
		for (int i = 0; i < 10; i++)
			v1.push_back(i);
		
		try
		{
			for (int i = 0; i < 12; i++)
				v1.pop_back();
			ft::vector<int> v2(1);
			v2 = v1; // test the copy assigment operator
			// ft::vector<int> v3(v1); //test copy constructor
			v2.erase(7);
			v2.insert(7, 10);
			print_varray(v1);
			print_varray(v2);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		



		// print_varray(v3);

	}
}
