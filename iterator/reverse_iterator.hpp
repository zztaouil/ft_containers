#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "random_access_iterator.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator{
		public:
			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type 		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			reverse_iterator(void) : iterator_type() {}
			explicit reverse_iterator (iterator_type it) : _it(it){}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it){
				this->_it = rev_it.base();
			}
			iterator_type	base(void) const{
				return _it;
			}
			reference	operator * (void) const{
				iterator_type tmp = _it;
				tmp--;
				return	*(tmp);
			}
			reverse_iterator	operator + (difference_type n) const{
				return reverse_iterator(_it - n);
			}
			reverse_iterator	&operator++(void){
				return reverse_iterator(--_it);
			}
			reverse_iterator	operator++(int){
				return reverse_iterator(_it--);
			}
			reverse_iterator	&operator+=(difference_type n){
				return reverse_iterator(_it -= n);
			}
			reverse_iterator	&operator-=(difference_type n){
				return reverse_iterator(_it += n);
			}
			reverse_iterator	operator-(difference_type n) const{
				return reverse_iterator(_it + n);
			}
			reverse_iterator	&operator--(void){
				return reverse_iterator(++_it);
			}
			reverse_iterator	operator--(int){
				return reverse_iterator(_it++);
			}
			pointer				operator->(void) const{
				return &(operator*());
			}
			reference			operator[] (difference_type n) const{
				return _it[n];
			}
		private:
			iterator_type	_it;
	};
	// Addition operator
	// Returns a reverse iterator pointing to the element located n positions away from the element 
	//pointed to by rev_it
	template <class Iterator>
		reverse_iterator<Iterator> operator + (typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator> &rev_it){
			return rev_it+n;	
		}
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type	operator- (
				const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() - rhs.base();
		}
	template <class Iterator>
		bool	operator== (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() == rhs.base();
		}
	template <class Iterator>
		bool	operator!= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() != rhs.base();
		}
	template <class Iterator>
		bool	operator< (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() < rhs.base();
		}
	template <class Iterator>
		bool	operator<= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() <= rhs.base();
		}
	template <class Iterator>
		bool	operator> (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() > rhs.base();
		}
	template <class Iterator>
		bool	operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs)
		{
			return lhs.base() >= rhs.base();
		}
// namespace ft
}
#endif
