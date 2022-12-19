#ifndef M_DEBUG
# define M_DEBUG 0
#endif

/*ORIGINALS*/
#include <vector>

/*OWN*/
#include "colors.hpp"
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "vector_iterator.hpp"



/*TEST FUKTION*/
void print_varray(ft::vector<int> &rhs)
{
	std::cout << rhs << std::endl;
}

/*MAIN*/
int main(void)
{
	std::cout << COLOR_RED << "\n\noriginal vector		" << COLOR_DEFAULT "|	" << COLOR_DEFAULT;
	std::cout << COLOR_GREEN << "my own vector\n" << COLOR_DEFAULT << std::endl;
	std::cout << COLOR_YELLOW << "Debug messages\n\n" << COLOR_DEFAULT << std::endl;

	//		THE ORIGINAL VECTOR CLASS
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << COLOR_RED << "push_back 10 times" << COLOR_DEFAULT << std::endl;
		std::vector<int> v1;
		for (int i = 0; i < 10; i++)
			v1.push_back(i);
		for (std::vector<int>::iterator iter = v1.begin(); iter != v1.end(); iter++)
			std::cout << *iter << " ";
		std::cout << " | | " << std::endl;
	}

	//		TESTING MY OWN VECTOR CLASS
	{
		std::cout << std::endl << std::string(60, '-') << std::endl;
		std::cout << COLOR_GREEN << "push_back 10 times" << COLOR_DEFAULT << std::endl;
		ft::vector<int> v1;

		try
		{
			for (int i = 0; i < 10; i++)
				v1.push_back(i);
			print_varray(v1);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
