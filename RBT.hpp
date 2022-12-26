#ifndef RBT_HPP
# define RBT_HPP

#include "utils.hpp"
#include "colors.hpp"
//#include "BRT_iterator.hpp"
#include <functional>
#include <memory>
#include <iostream>
#include <cstddef>
#define RED true
#define BLACK false

/*Intro to RBT: https://www.youtube.com/watch?v=qvZGUFHWChY*/

namespace ft
{
	template<typename T>
	struct Node
	{
		public:
			T*		content;
			Node	*parent;
			Node	*left_node;
			Node	*right_node;
			bool	color;
	};

	template<typename T>
	struct constNode
	{
		public:
			constNode(Node<T> node) : content(node->content), parent(node->parent), left_node(node->left_node), right_node(node->right_node), color(node->color) {}
			T* const	content;
			constNode	*parent;
			constNode	*left_node;
			constNode	*right_node;
			bool		color;
	};

	template<typename T, typename Compare, typename Alloc = std::allocator<T> >
	class RBT
	{
		public:
			typedef T													value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef Node<T>												node;
			typedef Node<T>*											node_pointer;
			typedef Node<const T>*										const_node_pointer;
			typedef RBT<value_type, key_compare, allocator_type>		tree_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			// typedef typename ft::RBT_iterator<node, tree_type>			iterator;
			// typedef typename ft::const_RBT_iterator<node, tree_type>	const_iterator;
			typedef ptrdiff_t											difference_type;
			typedef size_t												size_type;

/*--------CONSTRUCTORS----------------------*/

		RBT(const key_compare& comp = key_compare(), const allocator_type alloc = allocator_type())
		{
			if (M_DEBUG)
				std::cout << COLOR_YELLOW << "RBT default constructor" << std::endl;
			this->_compare = comp;
			this->_allocator = alloc;
			this->create_ends();
			this->_root = this->_end;
			this->_size = 0;
		}

		RBT (const RBT &rhs)
		{
			*this = rhs;
		}

		RBT &operator=(const RBT &rhs)
		{
			this->clear();
			this->_compare = rhs.getCompare();
			this->_allocator = rhs._allocator;
			this->_size = rhs._size;
			if (rhs.getRoot() != rhs.getEnd())
			{
				this->_root = this->_nodealloc.allocate(1);
				this->_root->parent = NULL;
				this->_root->left_node = NULL;
				this->_root->right_node = NULL;
				this->_root->color = BLACK;
				this->_root->content = this->_allocator.allocate(1);
				this->_allocator.construct(this->_root->content, *(rhs.getRoot()->content));
				this->copy_rec(this->_root, rhs.getRoot());
			}
			this->_end->parent = this->maximum(this->_root);
			this->_rend->parent = this->maximum(this->root);
			return (*this);
		}

		~RBT()
		{

		}

/*--------HELPER---------------------------*/

		void create_ends()
		{
			this->_end = this->_nodealloc.allocate(1);
			this->_end->content = this->_allocator.allocate(1);
			this->_allocator.construct(this->_end->content);
			this->_end->color = BLACK;
			this->_end->parent = NULL;
			this->_end->left_node = NULL;
			this->_end->right_node = NULL;
			this->_rend = this->_nodealloc.allocate(1);
			this->_rend->content = this->_allocator.allocate(1);
			this->_allocator.construct(this->_rend->content);
			this->_rend->color = BLACK;
			this->_rend->parent = NULL;
			this->_rend->left_node = NULL;
			this->_rend->right_node = NULL;
		}

		/*copys the node recursevly*/
		void copy_rec(node_pointer node, node_pointer rhs)
		{
			if (rhs->left_node)
			{
				node->left_node = this->_nodealloc.allocate(1);
				node->left_node->parent = node;
				node->left_node->left_node = NULL;
				node->left_node->right_node = NULL;
				node->left_node->color = rhs->left_node->color;
				node->left_node->content = this->_allocator.allocate(1);
				this->_allocator.construct(node->left_node->content, *(rhs->left_node->content));
				copy_rec(node->left_node, rhs->left_node);
			}
			if (rhs->right_node)
			{
				node->right_node = this->_nodealloc.allocate(1);
				node->right_node->parent = node;
				node->right_node->left_node = NULL;
				node->right_node->right_node = NULL;
				node->right_node->color = rhs->right_node->color;
				node->right_node->content = this->_allocator.allocate(1);
				this->_allocator.construct(node->right_node->content, *(rhs->right_node->content));
				copy_rec(node->right_node, rhs->right_node);

			}
		}

		void clear()
		{
			this->clear_subtree(this->_root);
			this->_root = this->_end;
			this->_size = 0;
		}

		key_compare getCompare() const
		{
			return (this->_compare);
		}

		allocator_type getAlloc() const
		{
			return (this->_allocator);
		}

		node_pointer getEnd() const
		{
			return (this->_end);
		}

		node_pointer getRend() const
		{
			return (this->_rend);
		}

		node_pointer getRoot() const
		{
			return (this->_root);
		}

		size_type size() const
		{
			return (this->_size);
		}
		
		size_type max_size() const
		{
			return (this->_allocator.max_size());
		}

		node_pointer minimum(node_pointer node) const
		{
			node_pointer temp;
			temp = node;
			if (!_root)
				return (this->_end);
			while (temp->lc)
				temp = temp->lc;
			return (temp);
		}

		node_pointer maximum(node_pointer node) const
		{
			node_pointer temp;
			temp = node;
			if (!_root)
				return (this->_end);
			while (temp->rc)
				temp = temp->rc;
			return (temp);
		}

/*-------FUNCTIONS----------------------------*/



/*-------ATTRIBUTES---------------------------*/
	private:
		node_pointer				_root;
		node_pointer				_end;
		node_pointer				_rend;
		allocator_type				_allocator;
		key_compare					_compare;
		std::allocator<Node<T> >	_nodealloc;
		size_type					_size;



	}; //class
} //namespace

#endif