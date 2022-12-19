#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include "vector_iterator.hpp"

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
			typedef T*													Pointer;
			typedef const T*											const_Pointer;
			typedef vector_iterator<Pointer, vector<T, Alloc> >			iterator;
			typedef vector_iterator<const_Pointer, vector<T, Alloc> >	const_iterator;
			// typedef reverse_vector_iterator<iterator>					reverse_iterator;
			// typedef reverse_vector_iterator<const_iterator>				const_reverse_iterator;

/*----------CONSTRUCTORS---------------------*/

			//default constructor
			vector(void) : _size(0), _capacity(10), _array(new int[_capacity])
			{

				//nothing here...
			}

			//default constructor with elements
			vector(int elements, int value = 0) : _size(elements), _capacity(elements + 5), _array(new int[_capacity])
			{
				for (int i = 0; i < size(); ++i)
				{
					_array[i] = value;
				}
			}

			//copy constructor
			vector(const vector& rhs) : _size(rhs._size), _capacity(rhs._capacity), _array(new int[_capacity])
			{
				for (int i = 0; i < rhs.size(); ++i)
				{
					_array[i] = rhs._array[i];
				}
			}

			//copy assigment operator overload
			vector& operator=(const vector &rhs)
			{
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
			//[] operator overload
			int& operator[](int index)
			{
				return (_array[index]);
			}

			int& front()
			{
				return (_array[0]);
			}

			int& back()
			{
				return (_array[_size - 1]);
			}

			void insert(int index, int value)
			{
				if ((index < 0) || (index >= _size))
					throw std::out_of_range("Insert - Index out of range");
				if (_size != _capacity)
				{
					for (int i = _size - 1; i >= index; --i)
						_array[i + 1] = _array[i];
					_array[index] = value;
					++_size;
				}
				else
				{
					_capacity *= 2;
					int *newArray = new int[_capacity];
					for (int i = 0; i < _size; ++i)
						newArray[i] = _array[i];
					delete[] _array;
					_array = newArray;
					insert(index, value);
				}
			}

			void erase(int index)
			{
				if ((index < 0) || (index >= _size))
					throw std::out_of_range("Erase - Index out of range");
				for (int i = index; i < _size - 1; ++i)
					_array[i] = _array[i + 1];
				--_size;
			}

			void clear(void)
			{
				_size = 0;
			}

			~vector(void)
			{
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
			T _size;
			T _capacity;
			T *_array;
			

		public:
			void push_back(int value)
			{ 
				if (_size < _capacity)
				{
					_array[_size] = value;
					_size++;
				}
				else
				{
					_capacity *= 2;
					int *newArray = new int[_capacity];
					for (int i = 0; i < _size; ++i)
						newArray[i] = _array[i];
					_array[_size] = value;
					_size++;
					delete [] _array;
					_array = newArray;
				}
			}

			void pop_back(void)
			{
				if (_size == 0)
					throw std::out_of_range("Poping back on empty vector");
				--_size;
				//this->erase(this->_end - 1);
			}

			bool empty(void) const
			{
				return (_size == 0);
			}

			int size(void) const
			{
				return (_size);
			}

			int capacity(void) const
			{
				return (_capacity);
			}

			bool operator==(const vector& rhs) const
			{
				if (size() != rhs.size())
					return (false);
				for (int i = 0; i < size(); ++i)
					if (_array[i] != rhs._array[i])
						return (false);
				return (true);
			}

			bool operator!=(const vector& rhs) const
			{
				return !(*this == rhs);
			}

			friend std::ostream& operator<<(std::ostream& ostr, const vector& rhs)
			{
				for (int i = 0; i < rhs._size; ++i)
					ostr << rhs._array[i] << " ";
				ostr << " | | ";
				for (int i = rhs._size; i < rhs._capacity; ++i)
					ostr << rhs._array[i] << " ";
				ostr << std::endl;
				return (ostr);
			}
};

}

#endif
