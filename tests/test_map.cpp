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
		std::cout << it->first << " | " << it->second << std::endl;
		it++;
	}
	std::cout << std::endl;
}

int main(void)
{

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "CREATE ORIGINAL MAP OBJECT" << COLOR_DEFAULT << std::endl;
	std::map<std::string, int> map_ori;

	/*-----VEC_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "CREATE OWN MAP OBJECT" << COLOR_DEFAULT << std::endl;
	ft::map<std::string, int> map_own;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "INSERT ELEMENTS" << COLOR_DEFAULT << std::endl;
	map_ori.insert(std::make_pair("zero", 0));
	map_ori.insert(std::make_pair("one", 1));
	map_ori.insert(std::make_pair("two", 2));
	map_ori.insert(std::make_pair("three", 3));
	map_ori.insert(std::make_pair("four", 4));
	map_ori.insert(std::make_pair("five", 5));
	map_ori.insert(std::make_pair("six", 6));
	map_ori.insert(std::make_pair("seven", 7));
	map_ori.insert(std::make_pair("eight", 8));
	map_ori.insert(std::make_pair("nine", 9));
	map_ori.insert(std::make_pair("ten", 10));
	printMap(map_ori);

	/*-----VEC_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "INSERT ELEMENTS" << COLOR_DEFAULT << std::endl;
	map_own.insert(ft::make_pair("zero", 0));
	map_own.insert(ft::make_pair("one", 1));
	map_own.insert(ft::make_pair("two", 2));
	map_own.insert(ft::make_pair("three", 3));
	map_own.insert(ft::make_pair("four", 4));
	map_own.insert(ft::make_pair("five", 5));
	map_own.insert(ft::make_pair("six", 6));
	map_own.insert(ft::make_pair("seven", 7));
	map_own.insert(ft::make_pair("eight", 8));
	map_own.insert(ft::make_pair("nine", 9));
	map_own.insert(ft::make_pair("ten", 10));
	printMap(map_own);

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;
}