/*	base class iterator	*/
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

template <class Category, class T, class Distance = ptrdiff_t,
	 class Pointer = T*, class Reference = T&>
	 class iterator{
	 public: 
		 typedef T		value_type;
		 typedef Distance	difference_type;
		 typedef Pointer		pointer;
		 typedef Reference	reference;
		 typedef Category	iterator_category;
	 };

#endif
