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
	std::cout << COLOR_MAGENTA << "Stuff to fix\n\n" << COLOR_DEFAULT << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::string(60, '-') << std::endl;
	/*-----VEC_ORI pushback 10 times-----*/
	std::cout << COLOR_RED << "push_back 10 times" << COLOR_DEFAULT << std::endl;
	std::vector<int> vec_ori;
	for (int i = 0; i < 10; i++)
		vec_ori.push_back(i);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;

	/*-----VEC_OWN pushback 10 times-----*/
	std::cout << COLOR_GREEN << "push_back 10 times" << COLOR_DEFAULT << std::endl;
	ft::vector<int> vec_own;

	try
	{
		for (int i = 0; i < 10; i++)
			vec_own.push_back(i);
		print_varray(vec_own);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI []-overload-----*/
	std::cout << COLOR_RED << "[]-overload" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_ori[2]: " << vec_ori[2] << std::endl;

	/*-----VEC_OWN []-overload-----*/
	std::cout << COLOR_GREEN << "[]-overload" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_own[2]: " << vec_own[2] << std::endl;


/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI front()-----*/
	std::cout << COLOR_RED << "front()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_ori.front(): " << vec_ori.front() << std::endl;

	/*-----VEC_OWN front()-----*/
	std::cout << COLOR_GREEN << "front()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_own.front(): " << vec_own.front() << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI back()-----*/
	std::cout << COLOR_RED << "back()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_ori.back(): " << vec_ori.back() << std::endl;

	/*-----VEC_OWN back()-----*/
	std::cout << COLOR_GREEN << "back()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_own.back(): " << vec_own.back() << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI insert() index-----*/
	std::cout << COLOR_RED << "vec_ori.insert(it + 3, 42)" << COLOR_DEFAULT << std::endl;
	std::vector<int>::iterator it_ori = vec_ori.begin();
	it_ori += 3;
	vec_ori.insert(it_ori, 42);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN insert() by index-----*/
	std::cout << COLOR_GREEN << "vec_own.insert(it + 3, 42)" << COLOR_DEFAULT << std::endl;
	ft::vector<int>::iterator it_own = vec_own.begin();
	it_own += 3;
	vec_own.insert(it_own, 42);
	print_varray(vec_own);
	}

/*---------------------------------------------------------------------------------------------------*/
	{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI insert() index with n-----*/
	std::cout << COLOR_RED << "vec_ori.insert(it + 3, 10, 21)" << COLOR_DEFAULT << std::endl;
	std::vector<int>::iterator it_ori = vec_ori.begin();
	it_ori += 3;
	vec_ori.insert(it_ori, 10, 21);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN insert() by index with n-----*/
	std::cout << COLOR_GREEN << "vec_own.insert(it + 3, 10, 21)" << COLOR_DEFAULT << std::endl;
	ft::vector<int>::iterator it_own = vec_own.begin();
	it_own += 3;
	vec_own.insert(it_own, 10, 21);
	print_varray(vec_own);
	}

/*---------------------------------------------------------------------------------------------------*/
	{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI insert() index by range-----*/
	std::cout << COLOR_RED << "vec_ori.insert(it, myarray, myarray + 4)" << COLOR_DEFAULT << std::endl;
	std::vector<int>::iterator it_ori = vec_ori.begin();
	it_ori += 3;
	int myarray[] = {69, 96, 420, 240};
	vec_ori.insert(it_ori, myarray, myarray + 4);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN insert() index by range-----*/
	std::cout << COLOR_GREEN << "vec_own.insert(it, myarray, myarray + 4)" << COLOR_DEFAULT << std::endl;
	ft::vector<int>::iterator it_own = vec_own.begin();
	it_own += 3;
	vec_own.insert(it_own, myarray, myarray + 4);
	print_varray(vec_own);
	}

/*---------------------------------------------------------------------------------------------------*/
	{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI erase()-----*/
	std::cout << COLOR_RED << "vec_ori.erase(it + 3)" << COLOR_DEFAULT << std::endl;
	std::vector<int>::iterator it_ori = vec_ori.begin();
	it_ori += 3;
	vec_ori.erase(it_ori);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN erase()-----*/
	std::cout << COLOR_GREEN << "vec_own.erase(it + 3)" << COLOR_DEFAULT << std::endl;
	ft::vector<int>::iterator it_own = vec_own.begin();
	it_own += 3;
	vec_own.erase(it_own);
	print_varray(vec_own);
	}

/*---------------------------------------------------------------------------------------------------*/
	{
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI erase() with range-----*/
	std::cout << COLOR_RED << "vec_ori.erase(it, it + 3)" << COLOR_DEFAULT << std::endl;
	std::vector<int>::iterator it_ori_start = vec_ori.begin();
	std::vector<int>::iterator it_ori_end = it_ori_start + 3;
	vec_ori.erase(it_ori_start, it_ori_end);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN erase() with range -----*/
	std::cout << COLOR_GREEN << "vec_own.erase(it, it + 3)" << COLOR_DEFAULT << std::endl;
	ft::vector<int>::iterator it_own_start = vec_own.begin();
	ft::vector<int>::iterator it_own_end = it_own_start + 3;
	vec_own.erase(it_own_start, it_own_end);
	print_varray(vec_own);
	}

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI pop_back()-----*/
	std::cout << COLOR_RED << "pop_back()" << COLOR_DEFAULT << std::endl;
	vec_ori.pop_back();
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;

	/*-----VEC_OWN pop_back()-----*/
	std::cout << COLOR_GREEN << "pop_back()" << COLOR_DEFAULT << std::endl;
	vec_own.pop_back();
	print_varray(vec_own);

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI size()-----*/
	std::cout << COLOR_RED << "size()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_ori.size(): " << vec_ori.size() << std::endl;

	/*-----VEC_OWN size()-----*/
	std::cout << COLOR_GREEN << "size()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_own.size(): " << vec_own.size() << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI capacity()-----*/
	std::cout << COLOR_RED << "capacity()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_ori.capacity(): " << vec_ori.capacity() << std::endl;

	/*-----VEC_OWN capacity()-----*/
	std::cout << COLOR_GREEN << "capacity()" << COLOR_DEFAULT << std::endl;
	std::cout << "vec_own.capacity(): " << vec_own.capacity() << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI iterator begin()-----*/
	std::cout << COLOR_RED << "vec_ori.begin(): " << *vec_ori.begin() << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN iterator begin()-----*/
	std::cout << COLOR_GREEN << "vec_own.begin(): " << *vec_own.begin() << COLOR_DEFAULT << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI iterator end()-----*/
	std::cout << COLOR_RED << "vec_ori.end(): " << *vec_ori.end() << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN iterator end()-----*/
	std::cout << COLOR_GREEN << "vec_own.end(): " << *vec_own.end() << COLOR_DEFAULT << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI resize()-----*/
	std::cout << COLOR_RED << "vec_ori.resize(10)" << COLOR_DEFAULT << std::endl;
	vec_ori.resize(10);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN vec_own.resize(10)-----*/
	std::cout << COLOR_GREEN << "vec_own.resize(10)" << COLOR_DEFAULT << std::endl;
	vec_own.resize(10);
	print_varray(vec_own);

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI size()-----*/
	std::cout << COLOR_RED << "size():" << vec_ori.size() << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN size()-----*/
	std::cout << COLOR_GREEN << "size():" << vec_own.size() << COLOR_DEFAULT << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI max_size()-----*/
	std::cout << COLOR_RED << "max_size():" << vec_ori.max_size() << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN max_size()-----*/
	std::cout << COLOR_GREEN << "max_size():" << vec_own.max_size() << COLOR_DEFAULT << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI reserve()-----*/
	std::cout << COLOR_RED << "reserve(100)" << COLOR_DEFAULT << std::endl;
	vec_ori.reserve(100);
	std::cout << vec_ori.capacity() << std::endl;

	/*-----VEC_OWN reserve()-----*/
	std::cout << COLOR_GREEN << "reserve(100)" << COLOR_DEFAULT << std::endl;
	vec_own.reserve(100);
	std::cout << vec_own.capacity() << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI assign()-----*/
	std::cout << COLOR_RED << "assign()" << COLOR_DEFAULT << std::endl;
	int array[] = {111, 222, 333, 444, 555, 666, 777, 888, 999};
	vec_ori.assign(array, array + 8);
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;


	/*-----VEC_OWN assign()-----*/
	std::cout << COLOR_GREEN << "assign()" << COLOR_DEFAULT << std::endl;
	vec_own.assign(array, array + 8);
	print_varray(vec_own);

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI clear()-----*/
	std::cout << COLOR_RED << "clear()" << COLOR_DEFAULT << std::endl;
	vec_ori.clear();
	for (std::vector<int>::iterator iter = vec_ori.begin(); iter != vec_ori.end(); iter++)
		std::cout << *iter << " ";
	std::cout << " | | " << std::endl;

	/*-----VEC_OWN clear()-----*/
	std::cout << COLOR_GREEN << "clear()" << COLOR_DEFAULT << std::endl;
	vec_own.clear();
	print_varray(vec_own);

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI empty()-----*/
	std::cout << COLOR_RED << "empty()" << COLOR_DEFAULT << std::endl;
	if (vec_ori.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*-----VEC_OWN empty()-----*/
	std::cout << COLOR_GREEN << "empty()" << COLOR_DEFAULT << std::endl;
	if (vec_own.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----VEC_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*-----VEC_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;
}
