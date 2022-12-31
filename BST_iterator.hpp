#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP

#ifndef M_DEBUG
# define M_DEBUG 0
#endif

#include "colors.hpp"
#include "iterator_traits.hpp"
#include "utils.hpp"
#include "BST.hpp"

namespace ft
{
	template <typename key, typename T>
	class BST_iter : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef key		 									key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef const value_type& 							const_reference;
			typedef typename BST<key_type, mapped_type>::node*	BST_node;

		private:
			mutable BST_node _p;
			mutable BST_node _first;
			mutable BST_node _last;
		
/*-------CONSTRUCTORS-------------------------------------------*/
		public:

			BST_iter(): _p(NULL), _first(NULL), _last(NULL)
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER default constructor" << COLOR_DEFAULT << std::endl; 
			}

			BST_iter(BST_node nd, BST_node f = NULL, BST_node l = NULL): _p(nd), _first(f), _last(l)
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER constructor with arguments" << COLOR_DEFAULT << std::endl; 
			}

			// template<typename n_ptr, typename v_type>
			// BST_iter(const BST_iter<n_ptr, v_type> &copy) : _p(copy._p), _first(copy._first), _last(copy._last)
			// {
			// 	if (M_DEBUG)
			// 		std::cout << COLOR_RED << "BST_ITER constructor with template" << COLOR_DEFAULT << std::endl;
			// }
			
			~BST_iter()
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER destructor" << COLOR_DEFAULT << std::endl; 
			}

			BST_iter(const BST_iter& it) : _p(it._p), _first(it._first), _last(it._last) 
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER copy constructor" << COLOR_DEFAULT << std::endl; 
			}
	
/*-----------GETTER-------------------------------*/

			BST_node getPtr() const 
			{
				return (this->_p);
			}

			BST_node getf() const 
			{
				return (this->_first);
			}

			BST_node getl() const 
			{
				return (this->_last);
			}
	
/*-----------OPERATORS-------------------------------------*/

			BST_iter& operator=(const BST_iter& other)
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER assigment operator" << COLOR_DEFAULT << std::endl; 
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			const BST_iter& operator=(const BST_iter& other) const
			{
				if (M_DEBUG)
					std::cout << COLOR_RED << "BST_ITER const assigment operator" << COLOR_DEFAULT << std::endl; 
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			BST_iter& operator++()
			{
				if(!_p)
					_p = _first;
				else if(_p->right != NULL){
					_p = _p->right;
					while(_p->left != NULL)
						_p = _p->left;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const BST_iter& operator++() const
			{
				if(!_p)
					_p = _first;
				else if(_p->right != NULL){
					_p = _p->right;
					while(_p->left != NULL)
						_p = _p->left;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			BST_iter operator++(int)
			{
				BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			const BST_iter operator++(int) const
			{
				BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			BST_iter& operator--()
			{
				if(!_p)
					_p = _last;
				else if(_p->left != NULL){
					_p = _p->left;
					while(_p->right != NULL)
						_p = _p->right;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const BST_iter& operator--() const
			{
				if(!_p)
					_p = _last;
				else if(_p->left != NULL){
					_p = _p->left;
					while(_p->right != NULL)
						_p = _p->right;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}


			BST_iter operator--(int)
			{
				BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			const BST_iter operator--(int) const
			{
				BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			// BST_iter operator-=(int value)
			// {
			// 	for (; value != 0; value--)
			// 		(*this)--;
			// }

			value_type* operator->()
			{
				return (&(_p->data));
			}

			const value_type* operator->() const
			{
				return (&(_p->data));
			}

			value_type& operator*()
			{
				return (static_cast<BST_node>(_p)->data);
			}

			const value_type& operator*()const
			{
				return (static_cast<BST_node>(_p)->data);
			}

			friend bool operator==(const BST_iter<key_type, mapped_type>& lhs, const BST_iter<key_type, mapped_type>& rhs)
			{
				return (lhs.getPtr() == rhs.getPtr());
			}

			friend bool operator!=(const BST_iter<key_type, mapped_type>& lhs, const BST_iter<key_type, mapped_type>& rhs)
			{
				return !(lhs.getPtr() == rhs.getPtr());
			}
	};

/*----------REVERSITERATOR--------------------------------------------------*/

	template <typename key, typename T>
	class reverse_BST_iter : public std::iterator<std::bidirectional_iterator_tag, T>
	{
		public:
			typedef key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef const value_type& 							const_reference;
			typedef typename BST<key_type, mapped_type>::node*	BST_node;

		private:
			mutable BST_node _p;
			mutable BST_node _first;
			mutable BST_node _last;
		
/*--------CONSTRUCTORS-----------------------------------*/
		public:

			reverse_BST_iter(): _p(NULL), _first(NULL), _last(NULL)
			{

			}

			reverse_BST_iter(BST_node nd, BST_node f = NULL, BST_node l = NULL): _p(nd), _first(f), _last(l)
			{

			}
			
			~reverse_BST_iter()
			{

			}

			reverse_BST_iter(const reverse_BST_iter& it) : _p(it._p), _first(it._first), _last(it._last)
			{

			}
		
/*-----------GETTER------------------------------*/

			BST_node getPtr() const 
			{
				return (this->_p);
			}

			BST_node getf() const 
			{
				return (this->_first);
			}

			BST_node getl() const 
			{
				return (this->_last);
			}

/*------------OPERATORS--------------------------------*/

			reverse_BST_iter& operator=(const reverse_BST_iter& other)
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			const reverse_BST_iter& operator=(const reverse_BST_iter& other) const
			{
				_p = other.getPtr();
				_first = other.getf();
				_last = other.getl();
				return (*this);
			}

			reverse_BST_iter& operator--()
			{
				if(!_p)
					_p = _first;
				else if(_p->right != NULL){
					_p = _p->right;
					while(_p->left != NULL)
						_p = _p->left;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const reverse_BST_iter& operator--() const
			{
				if(!_p)
					_p = _first;
				else if(_p->right != NULL){
					_p = _p->right;
					while(_p->left != NULL)
						_p = _p->left;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->right) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			// reverse_BST_iter operator-=(int value)
			// {
			// 	for (; value != 0; value--)
			// 		(*this)--;
			// }

			reverse_BST_iter operator++(int)
			{
				reverse_BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			const reverse_BST_iter operator++(int) const
			{
				reverse_BST_iter tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_BST_iter& operator++()
			{
				if(!_p)
					_p = _last;
				else if(_p->left != NULL){
					_p = _p->left;
					while(_p->right != NULL)
						_p = _p->right;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}

			const reverse_BST_iter& operator++() const
			{
				if(!_p)
					_p = _last;
				else if(_p->left != NULL){
					_p = _p->left;
					while(_p->right != NULL)
						_p = _p->right;
				}
				else{
					BST_node tmp = _p->parent;
					while (tmp != NULL && _p == tmp->left) {
						_p = tmp;
						tmp = tmp->parent;
					}
					_p = tmp;
				}
				return (*this);
			}


			reverse_BST_iter operator--(int)
			{
				reverse_BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			const reverse_BST_iter operator--(int) const
			{
				reverse_BST_iter tmp = *this;
				--(*this);
				return (tmp);
			}

			value_type* operator->()
			{
				return (&(_p->data));
			}

			const value_type* operator->() const
			{
				return (&(_p->data));
			}

			value_type& operator*()
			{
				return (static_cast<BST_node>(_p)->data);
			}

			const value_type& operator*()const
			{
				return (static_cast<BST_node>(_p)->data);
			}

			friend bool operator==(const reverse_BST_iter<key_type, mapped_type>& lhs, const reverse_BST_iter<key_type, mapped_type>& rhs)
			{
				return (lhs.getPtr() == rhs.getPtr());
			}

			friend bool operator!=(const reverse_BST_iter<key_type, mapped_type>& lhs, const reverse_BST_iter<key_type, mapped_type>& rhs)
			{
				return !(lhs.getPtr() == rhs.getPtr());
			}
	}; //class

} //namespace

#endif