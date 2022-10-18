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
			for (int i = 0; i < rhs.size(); ++i)
			{
				_array[i] = rhs._array[i];
			}
		}
		// vector operator=(vector &rhs);
		~vector(void)
		{
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
			std::cout << "push_back(" << value << ")" << std::endl;
			_array[_size] = value;
			_size++;
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
};

}

#endif
