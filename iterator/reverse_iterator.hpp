#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITEARTOR_HPP

# include "iterator_traits.hpp"
# include "iterators.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator{
		public:
			typedef Iterator iterator_type;
			typedef ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef ft::iterator_traits<Iterator>::value_type			value_type;
			typedef ft::iterator_traits<Iterator>::difference_type 		difference_type;
			typedef ft::iterator_traits<Iterator>::pointer				pointer;
			typedef ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator(void) : iterator() {}
			explict reverse_iterator (iterator_type it) : _it(it){}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it){
				this->_it = rev_it.base();
			}
			iterator_type	base(void) const{
				return _it;
			}

		private:
			iterator_type	_it;
	};
}

#endif