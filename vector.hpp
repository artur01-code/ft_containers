#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>

//https://www.youtube.com/watch?v=YpNCBw-cPWw : 23:51

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
			for (int i = 0; i < Size(); ++i)
			{
				_array[i] = value;
			}
		}
		vector(const vector& rhs) : _size(rhs._size), _capacity(rhs._capacity), _array(new int[_capacity])
		{
			for (int i = 0; i < rhs.Size(); i++)
			{
				_array[i] = rhs._array[i];
			}
		}

		// vector(const std::initilaizer_list<int>& list) : _size(0), _capacity(list.Size() + 5), _array(new int[_capacity])
		// {
		// 	for (int i = 0; i < list.Size(); ++i)
		// 		push_back(i);
		// }

		vector& operator=(const vector &rhs)
		{
			delete[] _array;
			this->_size = rhs._size;
			this->_capacity = rhs._capacity;
			this->_array = new int[_capacity];
			for (int i = 0; i < rhs.Size(); ++i)
			{
				_array[i] = rhs._array[i];
			}
			return (*this);
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
			// TODO: what if filled?
			// std::cout << "push_back(" << value << ")" << std::endl;
			if (_size < _capacity)
			{
				_array[_size] = value;
				_size++;
			}
			else
			{
				_capacity *= 2;
				int *newArray = new int[_capacity];
			}
		}

		bool Empty(void) const
		{
			return (_size == 0);
		}

		int Size(void) const
		{
			return (_size);
		}

		int Capacity(void) const
		{
			return (_capacity);
		}

		bool operator==(const vector& rhs) const
		{
			if (Size() != rhs.Size())
				return (false);
			for (int i = 0; i < Size(); ++i)
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
