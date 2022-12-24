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

//---------------BASE FUNCTION (HELPER)--------------------------------------------------------------

			pointer base() const { return (_ptr); }


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

//---------------VECTOR ITERATOR OPERATOR OVERLOADS----------------------------------------

            reference operator*(void) const { return (*_ptr); }

			vector_iterator& operator=(vector_iterator const &rhs) {
				_ptr = rhs._ptr;
				return (*this);
			}

			pointer operator->(void) const { return (_ptr); }

			reference operator[](const difference_type &offset) const { return(*(_ptr + offset)); }
			
			vector_iterator &operator++(void) {
				_ptr++;
				return (*this);
			}
			
			vector_iterator operator++(int) {
				vector_iterator ret(*this);
				_ptr++;
				return (ret);
			}

			vector_iterator &operator--(void) {
				_ptr--;
				return (*this);
			}
			
			vector_iterator operator--(int) {
				vector_iterator ret(*this);
				_ptr--;
				return (ret);
			}

			vector_iterator operator+(difference_type offset) const {

				return (vector_iterator(_ptr + offset));
			}

			vector_iterator  operator-(difference_type offset) const {

				return (vector_iterator(_ptr - offset));
			}

			vector_iterator &operator+=(difference_type offset) {
				_ptr += offset;
				return (*this);
			}
			
			vector_iterator &operator-=(difference_type offset) {
				_ptr -= offset;
				return (*this);
			}

        protected:
            pointer _ptr;
    };
}

#endif