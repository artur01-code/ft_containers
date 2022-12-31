#ifndef BST_HPP
# define BST_HPP

#ifndef M_DEBUG
# define M_DEBUG 0
#endif

#include "colors.hpp"
#include "iterator_traits.hpp"
#include "utils.hpp"
#include <cstdio>

/*https://iq.opengenus.org/implement-binary-search-tree-in-cpp/*/

namespace ft{

	template< typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > > 
	class BST
	{

		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

/*----------STRUCT--------------------------------------------------------------------*/
			struct node
			{
				node *left;
				node *right;
				node *parent;
				value_type data;
			};

/*-------ATTRIBUTES----------------------------------------------------------------------*/

		private:

			size_type		_size;
			allocator_type	_alloc;
			std::allocator<node> _node_alloc;

		public:
			node 		*_bst;
			key_compare	_comp;

/*----------CONSTRUCTORS------------------------------*/

			BST():  _size(0),_bst(NULL)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST default constructor" << COLOR_DEFAULT << std::endl;
			}

			BST& operator=(const BST& other)
			{
				_bst = other._bst;
				_size = other._size;
				_alloc = other._alloc;
				_node_alloc = other._node_alloc;
				return (*this);
			}

			~BST()
			{

			}

/*-----------HELPER--------------------*/

			bool empty() const
			{ 
				return (this->_size == 0); 
			}

			size_type size() const
			{ 
				return (this->_size); 
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			node* getRoot() const
			{
				return (this->_bst);
			}

			node* getToRoot() const
			{
				node* tmp = _bst;
				while(tmp->parent)
					tmp = tmp->parent;
				return (tmp);
			}

			bool _isLeaf(node *bst) const
			{
				return (bst->left == NULL && bst->right == NULL);
			}

			bool _isEmpty(node *bst) const
			{
				return (bst == NULL);
			}

			void _printMap(node* root)
			{
				if (root != NULL) {
					_printMap(root->left);
					std::cout << root->data.first << ":" << root->data.second << " ";
					_printMap(root->right);
				}
			}

			void _minNmax()
			{
				if(!_bst)
					return ;
				node* min_node = minNode(_bst);
				node* max_node = maxNode(_bst);
				std::cout << "Min node: (" << min_node->data.first << ", " << min_node->data.second << ")\n";
				std::cout << "Max node: (" << max_node->data.first << ", " << max_node->data.second << ")\n";
			}

			node* minNode(node* bst) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST minNode" << COLOR_DEFAULT << std::endl;
				node* current = bst;
				while (current && current->left != NULL)
					current = current->left;
				return (current);
			}

			node* 	maxNode(node* bst) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST maxNode" << COLOR_DEFAULT << std::endl;
				node* current = bst;
				while (current && current->right != NULL)
					current = current->right;
				return (current);
			}

			node *_new_node(const value_type &value, node* parent = NULL)
			{	
				node *new_node = _node_alloc.allocate(1);
				_alloc.construct(&(new_node->data), value);
				new_node->left = NULL;
				new_node->right = NULL;
				new_node->parent = parent;
				_size++;
				return (new_node);
			}

			void copyTree(node* rt = NULL)
			{
				if(!rt)
					return ;
				_insert(ft::pair<key_type, mapped_type>(rt->data.first, rt->data.second));
				copyTree(rt->left);
				copyTree(rt->right);
			}

			node*	begin(void) const
			{
				node*	tmp = this->_bst;
				while (tmp && tmp->left)
					tmp = tmp->left;
				return (tmp);
			}

			node*	end(void) const
			{
				node*	tmp = this->_bst;
				while (tmp && tmp->right)
					tmp = tmp->right;
				tmp = tmp->right;
				return (tmp);
			}
			
			node*	rbegin(void) const
			{
				node*	tmp = this->_bst;
				while (tmp && tmp->right)
					tmp = tmp->right;
				return (tmp);
			}

			node*	rend(void) const
			{
				node*	tmp = this->_bst;
				while (tmp && tmp->left)
					tmp = tmp->left;
				tmp = tmp->left;
				return (tmp);
			}

/*------------FUNCTIONS--------------------------------*/

			void _clear(node* nd = NULL)
			{
				if (_bst == NULL)
					return ;
				if (nd == NULL)
					nd = _bst;
				if (nd->right)
					_clear(nd->right);
				if (nd->left)
					_clear(nd->left);
				if(_isLeaf(nd)){
					if(nd->parent && nd->parent->right == nd)
						nd->parent->right = NULL;
					else if(nd->parent && nd->parent->left == nd)
						nd->parent->left = NULL;
					_node_alloc.deallocate(nd, 1);
				}
				if(nd == _bst)
					_bst = NULL;
				_size--;
			}

			node* _findNode(const key_type& key) const
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST _findNode" << COLOR_DEFAULT << std::endl;
				node* res = _bst;
				for (; res != NULL && extract_key(res->data) != key;)
				{
					if (_comp(key, extract_key(res->data)))
						res = res->left;
					else
						res = res->right;
				}
				return (res);
			}

			node* _insert(const value_type& value)
			{
				if (!_bst)
				{
					_bst = _new_node(value);
					return (_bst);
				}
				// std::cout << COLOR_RED << "value: " << value.first << COLOR_DEFAULT << std::endl;
				node* found = _findNode(value.first);
				// std::cout << COLOR_RED << "found: " << found << COLOR_DEFAULT << std::endl;
				if (found)
					return (found);
				node* tmp = NULL;
				found = _bst;
				while (found != NULL)
				{
					tmp = found;
					if(value.first < found->data.first)
						found = found->left;
					else
						found = found->right;
				}
				// std::cout << "new_node whithout !_bst" << std::endl;
				found = _new_node(value, tmp);
				if (value.first < tmp->data.first)
					tmp->left = found;
				else
					tmp->right = found;
				return (found);
			}

			void changeData(node* &curr, const value_type& val)
			{
				_alloc.construct(&(curr->data), val);
			}

/*HELPER FOR DELETENODE*/
			node* getPredecessor(node* node_val)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST getPredecessor" << COLOR_DEFAULT << std::endl;
				if (node_val->left != NULL)
					return (maxNode(node_val->left));
				else
				{
					node* parent = node_val->parent;
					while (parent != NULL && node_val == parent->left)
					{
						node_val = parent;
						parent = parent->parent;
					}
					node_val = parent;
				}
				return node_val;
			}

			node* getSuccessor(node* node_val) 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST getSuccessor" << COLOR_DEFAULT << std::endl;
				if (node_val->right != NULL)
					return minNode(node_val->right);
				else 
				{
					node* parent = node_val->parent;
					while (parent != NULL && node_val == parent->right) 
					{
						node_val = parent;
						parent = parent->parent;
					}
					node_val = parent;
				}
				return node_val;
			}

			static bool swapNodeValue(node* node1, node* node2) 
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST swapNodeValue" << COLOR_DEFAULT << std::endl;	
				node* parent1 = node1->parent;
				node* node1Left = node1->left;
				node* node1Right = node1->right;
				node* parent2 = node2->parent;
				node* node2Left = node2->left;
				node* node2Right = node2->right;

				if (parent1 != NULL && parent1->left == node1)
					parent1->left = node2;
				else if (parent1 != NULL)
					parent1->right = node2;
				node2->parent = parent1;

				if (parent2 != NULL && parent2->left == node2)
					parent2->left = node1;
				else if (parent2 != NULL)
					parent2->right = node1;
				if (parent2 != node1)
					node1->parent = parent2;
				else
					node1->parent = node2;

				if (node1Left == node2) {
					node2->left = node1;
					node2->right = node1Right;
				} else if (node1Right == node2) {
					node2->right = node1;
					node2->left = node1Left;
				} else {
					node2->left = node1Left;
					node2->right = node1Right;
				}

				if (node1Right && node1Right != node2)
					node1Right->parent = node2;
				if (node1Left && node1Left != node2)
					node1Left->parent = node2;

				node1->left = node2Left;
				if (node2Left)
					node2Left->parent = node1;
				node1->right = node2Right;
				if (node2Right)
					node2Right->parent = node1;
				
				if (parent1 == NULL)
					return false;
				return true;
			}

			void deleteLeaf(node* to_delete) {

				if (to_delete == NULL)
					return;
				node* parent = to_delete->parent;
				if (parent == NULL)
					_bst = NULL;
				else if (to_delete == parent->left)
					parent->left = NULL;
				else if (to_delete == parent->right)
					parent->right = NULL;
				_node_alloc.destroy(to_delete);
				_node_alloc.deallocate(to_delete, 1);
				this->_size--;
			}

			void _deleteNode(node* bst)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST _deleteNode" << COLOR_DEFAULT << std::endl;
				if (!bst)
					return ;
				if ((!bst->left) && (!bst->right)) //then it's a leaf
					deleteLeaf(bst); //_clear(bst);
				else
				{
					node* next;
					if (bst->left)
						next = getPredecessor(bst);
					else
						next = getSuccessor(bst);
					if (!swapNodeValue(bst, next))
						_bst = next;
					_deleteNode(bst);
				}

				
				/*
				node* tmp = NULL;
				if(!bst)
					return ;
				if(_isLeaf(bst))
					_clear(bst);
				else if(!_isLeaf(bst))
				{
					if(bst->left)
						tmp = maxNode(bst->left);
					else if(bst->right)
						tmp = minNode(bst->right); 
					changeData(bst, tmp->data);
					_deleteNode(tmp);
				}*/
			}

			size_type _erase(const Key &key)
			{
				if (M_DEBUG)
					std::cout << COLOR_YELLOW << "BST _erase" << COLOR_DEFAULT << std::endl;
				node*	found = _findNode(key);
				if(!_bst || !found)
					return (0);
				_deleteNode(found);
				return (1);
			}

			bool checkKey(const key_type &data, node* curr) const 
			{	
				if (curr == NULL)
					return false;
				if (curr->data.first == data)
					return true;
				else if (curr->data.first <= data)
					return checkKey(data, curr->right);
				else
					return checkKey(data, curr->left);
			}

/*---------------OPERATOR OVERLOAD----------------------*/
			bool operator==(const BST& rhs)
			{
				return (this->getRoot == rhs.getRoot());
			}
			
			bool operator!=(const BST& rhs)
			{
				return !(this->getRoot() == rhs.getRoot());
			}

	}; //class

	template <class value>
	value extract_key(value v)
	{
		if (M_DEBUG)
			std::cout << COLOR_YELLOW << "BST extract_key" << COLOR_DEFAULT << std::endl;
		return (v);
	}

	template <class first, class second>
	first extract_key(ft::pair<first, second> pair)
	{
		return (pair.first);
	}

} //end namepsace

#endif