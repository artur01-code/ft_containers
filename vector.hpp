#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <exception>

//https://www.youtube.com/watch?v=YpNCBw-cPWw

namespace ft {

template<typename T>
class vector
{
	public:
		vector(void) : _size(0), _capacity(10), _array(new int[_capacity])
		{
			//nothing here...
		}
		vector(int elements, int value = 0) : _size(elements), _capacity(elements + 5), _array(new int[_capacity])
		{
			for (int i = 0; i < size(); ++i)
			{
				_array[i] = value;
			}
		}
		vector(const vector& rhs) : _size(rhs._size), _capacity(rhs._capacity), _array(new int[_capacity])
		{
			for (int i = 0; i < rhs.size(); ++i)
			{
				_array[i] = rhs._array[i];
			}
		}

		// vector(const std::initilaizer_list<int>& list) : _size(0), _capacity(list.size() + 5), _array(new int[_capacity])
		// {
		// 	for (int i = 0; i < list.size(); ++i)
		// 		push_back(i);
		// }

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
			{
				std::cerr << "Insert - Index out of Range" << std::endl;
				return ;
				// throw (Exception);
			}
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

		void ersase(int index)
		{
			if ((index < 0) || (index >= _size))
			{
				std::cerr << "Erase - Index out of Range" << std::endl;
				return ;
				// throw (Exception);
			}
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

	private:
		int _size;
		int _capacity;
		int *_array;
		

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
			{
				std::cerr << "pop back on empty vector" << std::endl;
				return ;
				// throw PoppingBackEmptyVector();
			}
			--_size;
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

		class PoppingBackEmptyVector : std::exception
		{
			public:
				virtual const char* what() const throw()
				{
					return ("Pop back an empty vector!");
				}
		};

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
