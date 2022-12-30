#ifndef M_DEBUG
# define M_DEBUG 0
#endif

/*ORIGINALS*/
#include <vector>

/*OWN*/
#include "../colors.hpp"
#include "../vector.hpp"
#include "../iterator_traits.hpp"
#include "../vector_iterator.hpp"

void print_varray(ft::vector<std::string> &rhs)
{
	std::cout << rhs << std::endl;
}

void printSize(ft::vector<std::string> const &vct)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
}

void	checkErase(ft::vector<std::string> const &vct,
					ft::vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int main()
{
	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2));

	// checkErase(vct, vct.erase(vct.begin()));
	// checkErase(vct, vct.erase(vct.end() - 1));

	// checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	// checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);
	// checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	// checkErase(vct, vct.erase(vct.begin(), vct.end()));


	return (0);
}