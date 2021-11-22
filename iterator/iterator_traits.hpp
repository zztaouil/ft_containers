#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

namespace ft
{
	template<class Iterator>
	struct iterator_traits{
		typedef Iterator::difference_type difference_type;
		typedef Iterator::value_type	  value_type;
		typedef Iterator::pointer			pointer;
		typedef Iterator::reference			reference;
		typedef Iterator::iterator_category iterator_catergory;
	};
}


#endif