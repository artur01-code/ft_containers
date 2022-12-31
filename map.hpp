#ifndef MAP_HPP
# define MAP_HPP

#ifndef M_DEBUG
# define M_DEBUG 0
#endif

#include "colors.hpp"
#include "utils.hpp"
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "BST.hpp"
#include "BST_iterator.hpp"

namespace ft
{
	template< typename Key, typename T, typename Compare = std::less<Key>,
		typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::BST_iter<Key, T>						iterator;
			typedef const ft::BST_iter<Key, T>					const_iterator;
			typedef ft::reverse_BST_iter<Key, T>				reverse_iterator;
			typedef const ft::reverse_BST_iter<Key, T>			const_reverse_iterator;
			typedef typename BST<key_type, mapped_type>::node	node;

		private:

			BST<key_type, mapped_type>	_bst;
			key_compare					_comp;
			allocator_type				_alloc;


/*-----------CONSTRUCTORS-----------------------------------------------------------------------------------*/
		public:

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
				_bst(), _comp(comp), _alloc(alloc)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map default constructor" << COLOR_DEFAULT << std::endl;
			}

			template< class InputIt >
			map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()):
				_bst(), _comp(comp), _alloc(alloc)
			{
				for(;first != last; first++)
				{
					this->_bst._insert(*first);
				}
			}

			map(const map& other): _comp(other._comp), _alloc(other._alloc)
			{
				_bst.copyTree(other._bst.getToRoot());
			}

			~map()
			{
				this->clear();
			}

			map& operator=(const map& other)
			{
				if(*this == other)
					return (*this);
				clear();
				_bst.copyTree(other._bst.getToRoot());
				return (*this);
			}

/*-------------HELPER CLASS-----------------------------------------------------------------------*/
			class value_compare
			{
				friend class map;

				protected:
					key_compare	comp;
					value_compare(Compare c) : comp(c) 
					{

					}

				public:
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool operator()(const value_type & x, const value_type & y) const
					{
						return (comp(x.first, y.first));
					}
			};

/*------------ITERATOR FUNCTIONS--------------------------------------------------------------------*/

			iterator begin()
			{
				return (iterator(_bst.begin(), _bst.begin(), _bst.rbegin()));
			}

			const_iterator begin() const
			{
				return (const_iterator(_bst.begin(), _bst.begin(), _bst.rbegin()));
			}

			iterator end()
			{
				return (iterator(NULL, _bst.begin(), _bst.rbegin()));
			}

			const_iterator end() const
			{
				return (const_iterator(NULL, _bst.begin(), _bst.rbegin()));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(_bst.rbegin(), _bst.begin(), _bst.rbegin()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(_bst.rbegin(), _bst.begin(), _bst.rbegin()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(NULL, _bst.begin(), _bst.rbegin()));
			}
			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(NULL, _bst.begin(), _bst.rbegin()));
			}

/*------------HELPER-----------------------------------------------------------------------------------------------*/

			void printMap()
			{
				this->_bst._printMap(_bst.getRoot());
				std::cout << std::endl;
			}

			void minNmax()
			{
				this->_bst._minNmax();
			}

/*-----------ACCESS FUNCTIONS--------------------------------------------------------------------------------------*/

			/* Returns a copy of the allocator object associated with the map.*/
			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			/* Returns a copy of the comparison object used by the container to compare keys.*/
			key_compare key_comp() const
			{
				return (this->_comp);
			}

			/* Returns a comparison object that can be used to compare two elements to get whether
			 the key of the first one goes before the second.*/
			value_compare value_comp() const
			{
				return (value_compare(_comp));
			}

			/* Returns whether the map container is empty (i.e. whether its size is 0).*/
			bool empty() const
			{
				return (this->_bst.size() == 0);
			}

			/* Returns the number of elements in the map container.*/
			size_type size() const
			{
				return (this->_bst.size());
			}

			/* Returns the maximum number of elements that the map container can hold.*/
			size_type max_size() const
			{
				return (_bst.max_size());
			}

			/* Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.*/
			void clear()
			{
				_bst._clear(_bst.getRoot());
			}

/*------------FUNCTIONS--------------------------------------------------------------------------------------------*/

			/* Returns a reference to the mapped value of the element identified with key.*/
			mapped_type& at(const key_type& key)
			{
				iterator tmp = find(key);
				if(tmp == end())
					throw std::out_of_range("map::at");
				else
					return (tmp->second);
			}

			const mapped_type& at(const key_type& key) const
			{
				iterator tmp = find(key);
				if(tmp == end())
					throw std::out_of_range("map::at");
				else
					return (tmp->second);
			}

			mapped_type& operator[](const key_type& key)
			{
				return ((*((this->insert(ft::make_pair(key,mapped_type()))).first)).second);
			}

			/* Extends the container by inserting new elements, effectively increasing the container
			 size by the number of elements inserted.*/
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map insert with value" << COLOR_DEFAULT << std::endl;
				ft::pair<iterator, bool> tmp;
				if (_bst.checkKey(value.first, _bst.getRoot()))
					tmp.second = false;
				else
					tmp.second = true;
				tmp.first = iterator(_bst._insert(value));
				return (tmp);
			}

			iterator insert(iterator hint, const value_type& value)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map insert with hint" << COLOR_DEFAULT << std::endl;
				(void) hint; //useless
				iterator it = find(value.first);
				if (it != end())
					return (it);
				return (iterator(_bst._insert(value), _bst.getRoot()));
				
				/*
				if (hint != iterator())
					return (this->_bst._insert(value));
				return (iterator());*/
			}

			template< class InputIt > void insert(InputIt first, InputIt last)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map insert by range" << COLOR_DEFAULT << std::endl;
				for(; first != last; first++)
					_bst._insert(*first);
			}

			/* Removes from the map container a single element.*/
			void erase(iterator pos)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map erase by iterator" << COLOR_DEFAULT << std::endl;
				_bst._erase((*pos).first);
			}

			/* Removes from the map container a range of elements ([first,last)).*/
			void erase(iterator first, iterator last)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map erase by range" << COLOR_DEFAULT << std::endl;
				// while (first != last)
				// {
				// 	key_type key = (*first).first;
				// 	erase(key);
				// 	first++;
				// }
				while (first != last)
				{
					// std::cout << "key: " << (*first++).first << std::endl;
					// _bst._erase((*first++).first);
					// _bst._erase((*first).first);
					_bst._deleteNode(first++.getPtr());
					// first++; //zeigen die aufeinander? im Kreis? FML
					// std::cout << "next one" << std::endl;
				}
			}

			size_type erase(const key_type& key)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "Map erase by key" << COLOR_DEFAULT << std::endl;
				if (_bst._findNode(key))
				{
					_bst._erase(key);
					return (1);
				}
				return (0);

				// return (_bst._erase(key));
				
				/*
				node*	tmp = _bst._findNode(key);
				if (tmp)
				{
					_bst._erase(key);
					return (1);
				}
				return (0);
				*/
			}

			void swap(map& other)
			{
				BST<key_type, mapped_type>	tmp_bst = _bst;
				key_compare					tmp_comp = _comp;
				allocator_type				tmp_alloc = _alloc;
				
				_bst = other._bst;
				_comp = other._comp;
				_alloc = other._alloc;

				other._bst = tmp_bst;
				other._alloc = tmp_alloc;
				other._comp = tmp_comp;

			}

			/* Searches the container for elements with a key equivalent to key and returns the number of matches.*/
			size_type count(const key_type& key) const
			{
				if(!_bst._findNode(key))
					return (0);
				return (1);
			}

			/*Searches the container for an element with a key equivalent to key
			 and returns an iterator to it if found, otherwise it returns an iterator to map::end.*/
			iterator find(const key_type& key)
			{
				return (iterator(this->_bst._findNode(key)));
			}

			const_iterator find(const key_type& key) const
			{
				const_iterator res = _bst._findNode(key);
				if(res != NULL)
					return (res);
				else 
					return (const_iterator(end()));
			}

			/*Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			Because the elements in a map container have unique keys, the range returned will contain a single element at most.*/
			ft::pair<iterator,iterator> equal_range(const key_type& key)
			{
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator,const_iterator> equal_range(const key_type& key) const
			{
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			/*Returns an iterator pointing to the first element in the container
			 whose key is not considered to go before key (i.e., either it is equivalent or goes after).*/
			iterator lower_bound(const key_type& key)
			{
				iterator it  = begin();
				while (it != end() && _comp(it->first, key))
					++it;
				return (it);
			}

			const_iterator lower_bound(const key_type& key) const
			{
				const_iterator it  = begin();
				while (it != end() && _comp(it->first, key))
					++it;
				return (it);
			}

			/*Returns an iterator pointing to the first element in the container whose key is considered to go after k.*/
			iterator upper_bound(const key_type& key)
			{
				iterator it  = begin();
				while (it != end() && !_comp(key, it->first))
					++it;
				return (it);
			}

			const_iterator upper_bound(const key_type& key) const
			{
				const_iterator it  = begin();
				while (it != end() && !_comp(key, it->first))
					++it;
				return (it);
			}

	}; //class

/*--------SWAP & OPERATORS-----------------------------------------------------------------------------*/

	template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator==" << COLOR_DEFAULT << std::endl;
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator!=" << COLOR_DEFAULT << std::endl;
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator<" << COLOR_DEFAULT << std::endl;
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); 
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator<=" << COLOR_DEFAULT << std::endl;
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator>" << COLOR_DEFAULT << std::endl;
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "Map operator>=" << COLOR_DEFAULT << std::endl;
		return (lhs > rhs);
	}

} //namespace end

#endif