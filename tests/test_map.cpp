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
	std::cout << std::endl;
}

int main(void)
{

	std::cout << COLOR_RED << "\n\noriginal map		" << COLOR_DEFAULT "|	" << COLOR_DEFAULT;
	std::cout << COLOR_GREEN << "my own map\n" << COLOR_DEFAULT << std::endl;
	std::cout << COLOR_YELLOW << "Debug messages\n" << COLOR_DEFAULT << std::endl;
	std::cout << COLOR_MAGENTA << "Stuff to fix\n\n" << COLOR_DEFAULT << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "CREATE ORIGINAL MAP OBJECT" << COLOR_DEFAULT << std::endl;
	std::map<std::string, int> map_ori;

	/*-----MAP_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "CREATE OWN MAP OBJECT" << COLOR_DEFAULT << std::endl;
	ft::map<std::string, int> map_own;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI THIS IS A SAMPLE-----*/
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

	/*-----MAP_OWN THIS IS A SAMPLE-----*/
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
	/*-----MAP_ORI begin()-----*/
	std::cout << COLOR_RED << "map_ori.begin()" << COLOR_DEFAULT << std::endl;
	std::cout << map_ori.begin()->first << " | " << map_ori.begin()->second << std::endl;

	/*-----MAP_OWN begin()-----*/
	std::cout << COLOR_GREEN << "map_own.begin()" << COLOR_DEFAULT << std::endl;
	std::cout << map_own.begin()->first << " | " << map_own.begin()->second << std::endl;

	/*---------------------------------------------------------------------------------------------------*/

	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI end()-----*/
	std::cout << COLOR_RED << "map_ori.end() - 1" << COLOR_DEFAULT << std::endl;
	std::map<std::string, int>::iterator it_ori = map_ori.end();
	it_ori--;
	std::cout << it_ori->first << " | " << it_ori->second << std::endl;

	/*-----MAP_OWN end()-----*/
	std::cout << COLOR_GREEN << "map_own.end() - 1" << COLOR_DEFAULT << std::endl;
	ft::map<std::string, int>::iterator it_own = map_own.end();
	it_own--;
	std::cout << it_own->first << " | " << it_own->second << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI erase()-----*/
	std::cout << COLOR_RED << "map_ori.erase(it_ori)" << COLOR_DEFAULT << std::endl;
	map_ori.erase(it_ori);
	printMap(map_ori);

	/*-----MAP_OWN erase()-----*/
	std::cout << COLOR_GREEN << "map_own.erase(it_own)" << COLOR_DEFAULT << std::endl;
	map_own.erase(it_own);
	printMap(map_own);

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI count()-----*/
	std::cout << COLOR_RED << "map_ori.count(zero)" << COLOR_DEFAULT << std::endl;
	if (map_ori.count("zero"))
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*-----MAP_OWN count()-----*/
	std::cout << COLOR_GREEN << "map_own.count(zero)" << COLOR_DEFAULT << std::endl;
	if (map_own.count("zero"))
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI count()-----*/
	std::cout << COLOR_RED << "map_ori.count(one)" << COLOR_DEFAULT << std::endl;
	if (map_ori.count("one"))
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*-----MAP_OWN count()-----*/
	std::cout << COLOR_GREEN << "map_own.count(one)" << COLOR_DEFAULT << std::endl;
	if (map_own.count("one"))
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI find()-----*/
	std::cout << COLOR_RED << "map_ori.find(one)" << COLOR_DEFAULT << std::endl;
	it_ori = map_ori.find("one");
	std::cout << it_ori->first << "	|	" << it_ori->second << std::endl;

	/*-----MAP_OWN find()-----*/
	std::cout << COLOR_GREEN << "map_own.find(one)" << COLOR_DEFAULT << std::endl;
	it_own = map_own.find("one");
	std::cout << it_own->first << "	|	" << it_own->second << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI upper_bound()-----*/
	std::cout << COLOR_RED << "map_ori.upper_bound(five)" << COLOR_DEFAULT << std::endl;
	it_ori = map_ori.upper_bound("five");
	std::cout << it_ori->first << "	|	" << it_ori->second << std::endl;

	/*-----MAP_OWN upper_bound()-----*/
	std::cout << COLOR_GREEN << "map_own.upper_bound(five)" << COLOR_DEFAULT << std::endl;
	it_own = map_own.upper_bound("five");
	std::cout << it_own->first << "	|	" << it_own->second << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI upper_bound()-----*/
	std::cout << COLOR_RED << "map_ori.lower_bound(five)" << COLOR_DEFAULT << std::endl;
	it_ori = map_ori.lower_bound("five");
	std::cout << it_ori->first << "	|	" << it_ori->second << std::endl;

	/*-----MAP_OWN lower_bound()-----*/
	std::cout << COLOR_GREEN << "map_own.lower_bound(five)" << COLOR_DEFAULT << std::endl;
	it_own = map_own.lower_bound("five");
	std::cout << it_own->first << "	|	" << it_own->second << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----MAP_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*-----MAP_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;
}