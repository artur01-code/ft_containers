#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft {

	struct input_iterator_tag 
	{

	};

	struct forward_iterator_tag 
	{

	};

	struct bidirectional_iterator_tag : public input_iterator_tag 
	{

	};

	struct random_access_iterator_tag : public forward_iterator_tag
	{

	};

	struct output_iterator_tag : public bidirectional_iterator_tag 
	{

	};

	/* generic */
	template <typename T>
	struct iterator_traits 
	{
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::value_type			value_type;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;	
	};

	/* spezialization pointer */
	template <typename T>
	struct iterator_traits<T*> 
	{
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;	
	};

	/* spezialization const pointer */
	template <typename T>
	struct iterator_traits<const T*> 
	{
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;	
	};
}

#endif