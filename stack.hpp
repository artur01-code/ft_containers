#ifndef STACK_HPP
#define STACK_HPP

#ifndef M_DEBUG
# define M_DEBUG 0
#endif

#include <memory>
#include <iostream>
#include <stdexcept>
#include "colors.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace ft
{
	template< typename T, class Container = ft::vector<T> >
	class stack 
	{
		public:
			typedef Container									container_type;
			typedef typename Container::value_type				value_type;
			typedef typename Container::size_type				size_type;
			typedef typename Container::reference				reference;	
			typedef typename Container::const_reference			const_reference;

		protected:
			container_type	c;

/*---------------------------CONSTRUCTORS---------------------------------------*/
			
		public:
			explicit stack(const container_type& cont = container_type()) : c(cont) 
			{

			}

			stack(const stack& other) : c(other.c) 
			{

			}

			stack& operator=(const stack& rhs) 
			{
				c = rhs.c;
				return (*this);
			}

			~stack(void) 
			{

			}

/*---------------------------HELPERS----------------------------------------*/


			reference top()
			{
				return (c.back()); 
			}

			const_reference top() const 
			{
				return (c.back());
			}

			bool empty() const 
			{ 
				return (c.empty());
			}

			size_type size() const
			{
				return (c.size());
			}

			void push(const value_type& value)
			{
				c.push_back(value);
			}

			void pop()
			{
				c.pop_back();
			}


/*---------------------------RELATIONAL OPERATORS--------------------------------*/



			template< class _T, class _Container >
			friend bool operator==(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);

			template< class _T, class _Container >
			friend bool operator!=(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);

			template< class _T, class _Container >
			friend bool operator<(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);

			template< class _T, class _Container >
			friend bool operator<=(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);

			template< class _T, class _Container >
			friend bool operator>(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);

			template< class _T, class _Container >
			friend bool operator>=(const ft::stack<_T,_Container>& lhs, const ft::stack<_T,_Container>& rhs);
			
	}; //class


//---------------------------RELATIONAL OPERATORS (non-member)--------------------------------//


	template< class T, class Container >
	bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template< class T, class Container >
	bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{	
		return (lhs.c != rhs.c);
	}

	template< class T, class Container >
	bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template< class T, class Container >
	bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template< class T, class Container >
	bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template< class T, class Container >
	bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}

} // namespace ft

#endif
