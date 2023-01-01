#ifndef M_DEBUG
# define M_DEBUG 0
#endif

#include <stack>

#include "../stack.hpp"
#include "../colors.hpp"

template<typename T>
void printStack(T stack)
{
	T copy = stack;
	while (copy.size() != 0)
	{
		std::cout << copy.top() << std::endl;
		copy.pop();
	}
}

int main()
{
	std::stack<int> stack_ori;
	ft::stack<int> stack_own;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI empty()-----*/
	std::cout << COLOR_RED << "stack_ori.empty()" << COLOR_DEFAULT << std::endl;
	if (stack_ori.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*-----STACK_OWN.empty()-----*/
	std::cout << COLOR_GREEN << "stack_own.empty()" << COLOR_DEFAULT << std::endl;
	if (stack_own.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI push()-----*/
	std::cout << COLOR_RED << "stack_ori.push(n)" << COLOR_DEFAULT << std::endl;
	for (int i = 0; i < 9; i++)
		stack_ori.push(i);
	printStack(stack_ori);

	/*-----STACK_OWN push()-----*/
	std::cout << COLOR_GREEN << "stack_own.push(n)" << COLOR_DEFAULT << std::endl;
	for (int i = 0; i < 9; i++)
		stack_own.push(i);
	printStack(stack_own);

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI empty()-----*/
	std::cout << COLOR_RED << "stack_ori.empty()" << COLOR_DEFAULT << std::endl;
	if (stack_ori.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*-----STACK_OWN empty()-----*/
	std::cout << COLOR_GREEN << "stack_own.empty()" << COLOR_DEFAULT << std::endl;
	if (stack_own.empty())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI.size()-----*/
	std::cout << COLOR_RED << "stack_ori.size()" << COLOR_DEFAULT << std::endl;
	std::cout << stack_ori.size() << std::endl;

	/*-----STACK_OWN.size()-----*/
	std::cout << COLOR_GREEN << "stack_own.size()" << COLOR_DEFAULT << std::endl;
	std::cout << stack_own.size() << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI.top()-----*/
	std::cout << COLOR_RED << "stack_ori.top()" << COLOR_DEFAULT << std::endl;
	std::cout << stack_ori.top() << std::endl;

	/*-----STACK_OWN.top()-----*/
	std::cout << COLOR_GREEN << "stack_own.top()" << COLOR_DEFAULT << std::endl;
	std::cout << stack_own.top() << std::endl;

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI pop()-----*/
	std::cout << COLOR_RED << "stack_ori.pop() x6" << COLOR_DEFAULT << std::endl;
	for (int i = 0; i < 5; i++)
		stack_ori.pop();
	printStack(stack_ori);

	/*-----STACK_OWN pop()-----*/
	std::cout << COLOR_GREEN << "stack_own.pop() x6" << COLOR_DEFAULT << std::endl;
	for (int i = 0; i < 5; i++)
		stack_own.pop();
	printStack(stack_own);

	/*---------------------------------------------------------------------------------------------------*/
	std::cout << std::endl << std::string(60, '-') << std::endl;
	/*-----STACK_ORI THIS IS A SAMPLE-----*/
	std::cout << COLOR_RED << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

	/*-----STACK_OWN THIS IS A SAMPLE-----*/
	std::cout << COLOR_GREEN << "THIS IS A SAMPLE" << COLOR_DEFAULT << std::endl;

}