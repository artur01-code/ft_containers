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
			typedef reverse_vector_iterator<iterator>					reverse_iterator;
			typedef reverse_vector_iterator<const_iterator>				const_reverse_iterator;

/*----------CONSTRUCTORS---------------------*/

			//constructor
			explicit vector(const allocator_type &alloc = allocator_type()) : _size(0),_capacity(0), _alloc(alloc)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector default constructor" << COLOR_DEFAULT << std::endl;
				_array = NULL; 
			}
			
			//constructor with attributes
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _size(n), _capacity(n), _alloc(alloc)  
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector constructor with attributes" << COLOR_DEFAULT << std::endl;
				_array = _alloc.allocate(n);	
				for (size_type i = 0; i < n; i++)
					_alloc.construct(&(_array[i]), val);
			}

			//constructor with attributes (range)
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), \
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, \
				InputIterator>::type* = 0) : _size(0),_capacity(0), _alloc(alloc)  
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector constructor with attributes (range)" << COLOR_DEFAULT << std::endl;
				InputIterator it = first;
				while (it != last)
				{
					_size++;
					it++;
				}	
				_array = _alloc.allocate(_size);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&(_array[i]), *first++);
				_capacity = _size;
			}

			//copy constructor
			vector(const vector& rhs) : _size(rhs._size),_capacity(rhs._capacity), _alloc(rhs._alloc)  
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector copy constructor" << COLOR_DEFAULT << std::endl;
				_array = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&(_array[i]), rhs[i]);
			}

			//copy assigment operator overload
			vector &operator=(const vector& rhs) 
			{	
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector copy assigment operator overload" << COLOR_DEFAULT << std::endl;
				if (_array != rhs._array)
				{
					_alloc = rhs._alloc;
					assign(rhs.begin(), rhs.end());
				}
				return (*this);
			}


/*---------------------------DESTRUCTOR----------------------------------------*/

			
			~vector(void) 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector default destructor" << COLOR_DEFAULT << std::endl;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&(_array[i]));
				_alloc.deallocate(_array, _capacity);
			}

/*-------PRIVATES ATTRIBUTES-----------*/
		private:
			size_t			_size;
			size_t			_capacity;
			pointer			_array; //same as T*
			allocator_type	_alloc;

/*-------HELPER FUNCTIONS---------------------------*/

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
			


/*----------ITERATOR FUNCTIONS---------------------*/
		public:
			iterator begin(void) { return( iterator(_array) ); }
			iterator end(void) { return(iterator(_array + _size)); }
			const_iterator begin(void) const { return( const_iterator(_array)); }
			const_iterator end(void) const { return(const_iterator(_array + _size)); }
			//reverse_iterator [...]


/*----------FUNCTIONS---------------------*/

			reference at(size_type pos) 
			{
				if (pos >= _size)
					throw std::out_of_range("vector.at() call out of range");
				return(_array[pos]);
			}

			const_reference at(size_type pos) const 
			{
				if (pos >= _size)
					throw std::out_of_range("vector.at() call out of range");
				return(_array[pos]);
			}

			reference operator[](unsigned int index) 
			{	
				if (index >= _size)
					throw std::out_of_range("vector[index] call out of range");
				return *(_array + index);
			}

			const_reference operator[](unsigned int index) const 
			{	
				if (index >= _size)
					throw std::out_of_range("vector[index] call out of range");
				return *(_array + index);
			}

			reference front()
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector front" << COLOR_DEFAULT << std::endl;
				return (_array[0]);
			}

			const_reference front() const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector front const" << COLOR_DEFAULT << std::endl;
				return (_array[0]);
			}

			reference back()
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector back" << COLOR_DEFAULT << std::endl;
				return (_array[_size - 1]);
			}

			const_reference back() const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector back const" << COLOR_DEFAULT << std::endl;
				return (_array[_size - 1]);
			}

			T* data(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector data" << COLOR_DEFAULT << std::endl;
				return (_array);
			}

			const T* data(void) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector data const" << COLOR_DEFAULT << std::endl;
				return (_array);
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
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) 
			{
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

			//erase by index
			iterator erase(iterator position) 
			{
				size_type pos_counter = 0;
				for (iterator it = this->begin(); it != position; it++)
					pos_counter++;
				_alloc.destroy(&(_array[pos_counter]));
				if (pos_counter < (_size - 1))
				{
					for (size_type i = pos_counter; i < _size - 1; i++)
					{
						_alloc.construct(&(_array[i]), _array[i + 1]);
						_alloc.destroy(&(_array[i + 1]));
					}
				}
				_size--;
				return (iterator(&(_array[pos_counter])));
			}

			//earse a range
			iterator erase(iterator first, iterator last) 
			{
				iterator tmp = first;
				difference_type tmp_size = last - first;
				while (first != this->end())
				{
					_alloc.destroy(&(*first));
					if (last != this->end())
					{
						_alloc.construct(&(*first), *last);
						last++;
					}
					first++;
				}
				_size -= tmp_size;
				return (tmp);
			}

			void clear(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector clear" << COLOR_DEFAULT << std::endl;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&(_array[i]));
				_size = 0;
			}

			/*https://cplusplus.com/reference/vector/vector/resize/*/
			void resize(size_type n, value_type val = value_type())
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector rezize" << std::endl;
				if (n < _size)
					for (size_type i = n - 1; i < _size; i++)
						_alloc.destroy(&(_array[i]));
				else if (n > _size)
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&(_array[i]), val);
				else if (n > _capacity)
				{
					size_type tmp_capacity = _capacity;
					while (tmp_capacity < n)
						tmp_capacity *= 2;
					realloc(tmp_capacity, val);
				}
				_size = n;
			}

			void reserve(size_type new_cap) {

				pointer tmp = NULL;
				if (new_cap > _alloc.max_size())
					throw std::length_error("Reserve: too big new cap");
				else if (new_cap < _capacity)
					return;
				try 
				{
					tmp = _alloc.allocate(new_cap);
				} 
				catch (std::bad_alloc &e) 
				{
					throw e;
				}
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&(tmp[i]), _array[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&(_array[i]));
				_alloc.deallocate(_array, _capacity);
				_array = tmp;
				_capacity = new_cap;
			}

			//https://cplusplus.com/reference/vector/vector/assign/
			//destorys the array and creates a new given by the passed range
			template< class InputIterator >
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) 
			{
				
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&(_array[i]));
				size_type new_size = 0;
				InputIterator tmp = first;
				while (tmp++ != last)
					new_size++;
				if (new_size > _capacity)
					realloc(new_size);
				for (size_type i = 0; i < new_size; i++)
					_alloc.construct(&(_array[i]), *first++);
				if (new_size < _size)
				{
					for (size_type i = new_size; i < _size; i++)
						_alloc.destroy(&(_array[i]));
				}
				_size = new_size;
			}

			//destroys the content of the array and replaces it with the new count times
			void assign(size_type count, const T& value) 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector assign" << COLOR_DEFAULT << std::endl;
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&(_array[i]));
				if (_size < count)
					realloc(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(&(_array[i]), value);
				_size = count;
			}

			void push_back(const value_type& val)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector push_back" << COLOR_DEFAULT << std::endl;
				if (!_capacity)
					realloc(1);
				if (_size == _capacity)
					realloc(_capacity * 2);
				_alloc.construct(_array + _size, val);
				this->_size++;
			}

			void pop_back(void)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector pop_back" << COLOR_DEFAULT << std::endl;
				if (!_size)
					return;
				_alloc.destroy(&(_array[_size - 1]));
				_size--;
			}

			void swap (vector& x) 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector swap" << COLOR_DEFAULT << std::endl;
				pointer tmp_ptr = _array;
				allocator_type tmp_alloc = _alloc;
				size_type tmp_size = _size;
				size_type tmp_capacity = _capacity;
				
				_array = x._array;
				_alloc = x._alloc;
				_size = x._size;
				_capacity = x._capacity;
				
				x._array = tmp_ptr;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			bool empty(void) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector empty" << COLOR_DEFAULT << std::endl;
				return (_size == 0);
			}

			size_type size(void) const 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector size" << COLOR_DEFAULT << std::endl;
				return(_size);
			}
			
			size_type max_size(void) const 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Vector max_size" << COLOR_DEFAULT << std::endl;
				return(_alloc.max_size());
			}

			size_type capacity(void) const
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
	}
}//namespace


namespace std {

	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		
		lhs.swap(rhs);
	}
} // namespace std

#endif
