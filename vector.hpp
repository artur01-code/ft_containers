#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include "vector_iterator.hpp"
#include "utils.hpp"

//https://www.youtube.com/watch?v=YpNCBw-cPWw

namespace ft {

	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T													value_type;
			typedef Alloc												allocator_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef T&													reference;
			typedef const T												const_reference;
			typedef T*													pointer;
			typedef const T*											const_pointer;
			typedef vector_iterator<pointer, vector<T, Alloc> >			iterator;
			typedef vector_iterator<const_pointer, vector<T, Alloc> >	const_iterator;
			// typedef reverse_vector_iterator<iterator>					reverse_iterator;
			// typedef reverse_vector_iterator<const_iterator>				const_reverse_iterator;

/*----------CONSTRUCTORS---------------------*/

			//default constructor
			vector(void) : _size(0), _capacity(10), _array(new int[_capacity])
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector default constructor" << COLOR_DEFAULT << std::endl;
				//nothing here...
			}

			//default constructor with elements
			vector(int elements, int value = 0) : _size(elements), _capacity(elements + 5), _array(new int[_capacity])
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector default constructor with elements" << COLOR_DEFAULT << std::endl;
				for (int i = 0; i < size(); ++i)
				{
					_array[i] = value;
				}
			}

			//copy constructor
			vector(const vector& rhs) : _size(rhs._size), _capacity(rhs._capacity), _array(new int[_capacity])
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector copy constructor" << COLOR_DEFAULT << std::endl;
				for (int i = 0; i < rhs.size(); ++i)
				{
					_array[i] = rhs._array[i];
				}
			}

			//copy assigment operator overload
			vector& operator=(const vector &rhs)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector copy assigment operator overload" << COLOR_DEFAULT << std::endl;
				if (rhs._size > _size)
				{
					delete[] _array;
					this->_capacity = rhs._capacity + 5;
					this->_array = new int[_capacity];
				}
				for (int i = 0; i < rhs.size(); ++i)
				{
					_array[i] = rhs._array[i];
				}
				this->_size = rhs._size;
				return (*this);
			}

			~vector(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector default destructor" << COLOR_DEFAULT << std::endl;
				std::cout << "size: " << this->_size << " capacity: " << _capacity << std::endl;
				if (_capacity > 0)
					delete[] _array;
			}

			// //Iterator for vector https://www.youtube.com/watch?v=F9eDv-YIOQ0
			// VectorIterator begin()
			// {
			// 	return (VectorIterator(_data));
			// }

			// VectorIterator end()
			// {
			// 	return (VectorIterator(_data + _size));
			// }

		private:
			size_t			_size;
			size_t			_capacity;
			pointer			_array; //same as T*
			allocator_type	_alloc;

		//reallocates the memory given by the new capacity
		void realloc(size_type new_capacity, value_type val = value_type())
		{
			if (M_DEBUG)
				std::cout << COLOR_YELLOW << "realloc(" << new_capacity << ")" << COLOR_DEFAULT << std::endl;
			pointer tmp =_alloc.allocate(new_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&(tmp[i]), _array[i]);
			for (size_type i = _size; i < new_capacity; i++)
				_alloc.construct(&(tmp[i]), val);
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&(_array[i]));
			_alloc.deallocate(_array, _capacity);
			_array = tmp;
			_capacity = new_capacity;
		}
			

		public:

/*----------ITERATOR FUNCTIONS---------------------*/
			iterator begin(void) { return( iterator(_array) ); }
			iterator end(void) { return(iterator(_array + _size)); }
			const_iterator begin(void) const { return( const_iterator(_array)); }
			const_iterator end(void) const { return(const_iterator(_array + _size)); }
			//reverse_iterator [...]


/*----------FUNCTIONS---------------------*/

			int& front()
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector front" << COLOR_DEFAULT << std::endl;
				return (_array[0]);
			}

			int& back()
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector back" << COLOR_DEFAULT << std::endl;
				return (_array[_size - 1]);
			}

			//takes the position aka index
			iterator insert(iterator position, const value_type& val)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "insert at position" << COLOR_DEFAULT << std::endl;
				if (!_array)
				{
					_array = _alloc.allocate(1);
					_alloc.construct(&_array[0], val);
					_size = 1;
					_capacity = 1;
					return (iterator(&_array[0]));
				}
				size_type pos_counter = 0;
				for (iterator it = this->begin(); it != position; it++)
					pos_counter++;
				if (_size == _capacity)
				{
					if (!_capacity)
						realloc(1);
					else
						realloc(_capacity * 2);
				}
				for (size_type i = _size; i > pos_counter; i--)
				{
					_alloc.construct(&(_array[i]), _array[i - 1]);
					_alloc.destroy(&(_array[i - 1]));
				}
				_alloc.construct(&(_array[pos_counter]), val);
				_size++;
				return (iterator(&(_array[pos_counter])));
			}

			//takes the position aka index with n
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "insert at position with n" << COLOR_DEFAULT << std::endl;
				if (!_array)
				{
					_array = _alloc.allocate(n);
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&(_array[i]), val);
					_size = n;
					_capacity = n;
					return ;
				}
				size_type pos_counter = 0;
				for (iterator it = this->begin(); it != position; it++)
					pos_counter++;
				if (_size + n >= _capacity)
				{
					if (!_capacity)
						realloc(n);
					else
						realloc(_size + n);
				}
				for (size_type i = (_size + n - 1); i >= pos_counter + n; i--)
				{
					_alloc.construct(&(_array[i]), _array[i - n]);
					_alloc.destroy(&(_array[i - n]));
				}
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&(_array[pos_counter + i]), val);
				_size += n;
			}

			//insert with range
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
				
				if (first == last)
					return;
				size_type tmp_size = 0;
				for (InputIterator tmp_it = first; tmp_it != last; tmp_it++)
					tmp_size++;
				
				pointer dup_start = NULL;
				pointer dup_end = NULL;
				size_type dup_capacity = 0;
				pointer pointer_pos = position.base();
				InputIterator it_first = first;
				InputIterator it_last= last;
				pointer tmp = _array;

				if (_size + tmp_size >= _capacity)
				{
					dup_capacity = _size + tmp_size;
					if (_size + tmp_size > _capacity * 2)
						dup_capacity = _size + tmp_size;
					else
						dup_capacity = _capacity * 2;
					dup_start = _alloc.allocate(dup_capacity);
					dup_end = dup_start;
					try 
					{
						while(tmp != pointer_pos)
						{
							_alloc.construct(dup_end, *tmp);
							_alloc.destroy(tmp);
							dup_end++;
							tmp++;
						}
						while (it_first != it_last)
						{
							_alloc.construct(dup_end, *it_first);
							dup_end++;
							it_first++;
						}
						while (tmp != (_array + _size))
						{
							_alloc.construct(dup_end, *tmp);
							_alloc.destroy(tmp);
							dup_end++;
							tmp++;
						}
					}
					catch (...)
					{
						while (dup_start != dup_end)
							_alloc.destroy(dup_end--);
						_alloc.destroy(dup_start);
						_alloc.deallocate(dup_start, dup_capacity);
						throw;
					}
					_alloc.deallocate(_array, _capacity);
					_array = dup_start;
					_capacity = dup_capacity;
					_size += tmp_size;
				}
				else {

					size_type pos_counter = 0;
					for (iterator it = this->begin(); it != position; it++)
						pos_counter++;

					for (size_type i = (_size + tmp_size - 1); i >= (pos_counter + tmp_size); i--)
					{
						_alloc.construct(&(_array[i]), _array[i - tmp_size]);
						_alloc.destroy(&(_array[i - tmp_size]));
					}
					for (size_type i = 0; i < tmp_size; i++)
						_alloc.construct(&(_array[pos_counter + i]), *first++);
					_size += tmp_size;
				}
			}

			/*NEEDS TO TAKE AN ITERATOR*/
			void erase(int index)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector erase" << COLOR_DEFAULT << std::endl;
				if ((index < 0) || ((size_t)index >= _size))
					throw std::out_of_range("Erase - Index out of range");
				for (size_t i = index; i < _size - 1; ++i)
					_array[i] = _array[i + 1];
				--_size;
			}

			void clear(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector clear" << COLOR_DEFAULT << std::endl;
				_size = 0;
			}

			void push_back(int value)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector push_back" << COLOR_DEFAULT << std::endl;
				if (_size < _capacity)
				{
					_array[_size] = value;
					_size++;
				}
				else
				{
					_capacity *= 2;
					int *newArray = new int[_capacity];
					for (size_t i = 0; i < _size; ++i)
						newArray[i] = _array[i];
					_array[_size] = value;
					_size++;
					delete [] _array;
					_array = newArray;
				}
			}

			void pop_back(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector pop_back" << COLOR_DEFAULT << std::endl;
				if (_size == 0)
					throw std::out_of_range("Poping back on empty vector");
				--_size;
				//this->erase(this->_end - 1);
			}

			bool empty(void) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector empty" << COLOR_DEFAULT << std::endl;
				return (_size == 0);
			}

			int size(void) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector size" << COLOR_DEFAULT << std::endl;
				return (_size);
			}

			int capacity(void) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector capacity" << COLOR_DEFAULT << std::endl;
				return (_capacity);
			}

/*----------OPERATORS-------------*/
			//not sure if they should be non member operators
			int& operator[](int index)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector []-overload" << COLOR_DEFAULT << std::endl;
				return (_array[index]);
			}

			bool operator==(const vector& rhs) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector ==operator" << COLOR_DEFAULT << std::endl;
				if (size() != rhs.size())
					return (false);
				for (int i = 0; i < size(); ++i)
					if (_array[i] != rhs._array[i])
						return (false);
				return (true);
			}

			/* moved to non member operators
			bool operator!=(const vector& rhs) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector !=operator" << COLOR_DEFAULT << std::endl;
				return !(*this == rhs);
			}*/

			friend std::ostream& operator<<(std::ostream& ostr, const vector& rhs)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector <<operator" << COLOR_DEFAULT << std::endl;
				for (size_t i = 0; i < rhs._size; ++i)
					ostr << rhs._array[i] << " ";
				ostr << " | | ";
				for (size_t i = rhs._size; i < rhs._capacity; ++i)
					ostr << rhs._array[i] << " ";
				ostr << std::endl;
				return (ostr);
			}
	}; //class

/*----------OPERATORS (non member)---------------------*/

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator!=" << COLOR_DEFAULT << std::endl;	
		return (!(lhs == rhs));
	}
/*
	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator==" << COLOR_DEFAULT << std::endl;	
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator<" << COLOR_DEFAULT << std::endl;
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
				
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator<=" << COLOR_DEFAULT << std::endl;
		return (!(rhs < lhs));
	}

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator>" << COLOR_DEFAULT << std::endl;	
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) 
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "operator>=" << COLOR_DEFAULT << std::endl;	
		return (!(lhs < rhs));
	}*/

}//namespace

#endif
