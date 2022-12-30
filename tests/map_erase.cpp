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

template<typename T>
void printMap(T map)
{
	typename T::iterator it = map.begin();
	while (it != map.end())
	{
		std::cout << it->first << "	|	" << it->second << std::endl;
		it++;
	}
	std::cout << "size: " << map.size() << std::endl;
		std::cout << "max_size: " << map.max_size() << std::endl;
	std::cout << std::endl;
}

int main()
{
	ft::map<std::string, int> mp;

	mp.insert(ft::make_pair("zero", 0));
	mp.insert(ft::make_pair("one", 1));
	mp.insert(ft::make_pair("two", 2));
	mp.insert(ft::make_pair("three", 3));
	mp.insert(ft::make_pair("four", 4));
	mp.insert(ft::make_pair("five", 5));
	mp.insert(ft::make_pair("six", 6));
	mp.insert(ft::make_pair("seven", 7));
	mp.insert(ft::make_pair("eight", 8));
	mp.insert(ft::make_pair("nine", 9));
	mp.insert(ft::make_pair("ten", 10));

	mp.erase(--(--(--mp.end())), --mp.end());
	printMap(mp);
}