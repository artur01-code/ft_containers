#ifndef VECTOR_ITERATOR
# define VECTOR_ITERATOR

#include <iostream>
#include <cstddef>
// #include "utils.hpp"
#include "iterator_traits.hpp"

namespace ft
{

    template<typename T, typename Container>
    class vector_iterator
    {
/*------VECTOR ITERATOR TYPEDEFS : ITERATOR TRAITS------*/
        public:
            typedef T                                                   iterator_type;
            typedef typename ft::iterator_traits<T>::iterator_category  iterator_category;
            typedef typename ft::iterator_traits<T>::value_type         value_type;
            typedef typename ft::iterator_traits<T>::difference_type    difference_type;
            typedef typename ft::iterator_traits<T>::pointer            pointer;
            typedef typename ft::iterator_traits<T>::reference          reference;


/*------VECTOR ITERATOR CONSTRUCTORS------*/
		public:
			vector_iterator(void) : _ptr(NULL) {}
			vector_iterator(pointer ptr) : _ptr(ptr) {}
			//below added for const/non-const
			// template<typename _T>
			// vector_iterator(const vector_iterator<_T, typename ft::enable_if<ft::are_same<_T, typename Container::pointer>::value, Container>::type>& copy) : _ptr(copy.base()) {}		
			//end addition
			vector_iterator(const vector_iterator &copy) : _ptr(copy.base()) {}
			~vector_iterator() {}

        protected:
            pointer _ptr;
    };
}

#endif