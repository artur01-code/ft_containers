#ifndef M_DEBUG
# define M_DEBUG 0
#endif

/*ORIGINALS*/
#include <map>

/*OWN*/
#include "../colors.hpp"
#include "../map.hpp"
#include "../BST.hpp"
#include "../BST_iterator.hpp"

int main()
{
	ft::map<int, int> const mp;
	ft::map<int, int>::iterator it = mp.begin(); // <-- error expected

	// std::map<int, int> const mp2;
	// std::map<int, int>::iterator it2 = mp2.begin(); // <-- error expected

	(void)it;
	return (0);
}