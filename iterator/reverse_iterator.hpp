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

				reverse_iterator(void): _it(0) {}
				explicit reverse_iterator (iterator_type it) : _it(it){}
				template <class Iter>
					reverse_iterator(reverse_iterator<Iter> const &rev_it){
						_it = rev_it.base();
					}
				reverse_iterator	&operator= (reverse_iterator const &obj){
					//std::cerr << "reverse iterator Assignment operator overload" << std::endl;
					if (this != &obj){
						_it = obj.base();
					}
					return *this;
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
					iterator_type tmp = _it;
					tmp -= n;
					return reverse_iterator(tmp);
				}
				reverse_iterator	&operator++(int){
					reverse_iterator* tmp = this;
					this->_it--;
					return *tmp;
				}
				reverse_iterator	operator++(void){
					return reverse_iterator(_it--);
				}
				reverse_iterator	&operator+=(difference_type n){
					_it -= n;
					return *this;
				}
				reverse_iterator	&operator-=(difference_type n){
					_it += n;
					return *this;
				}
				reverse_iterator	operator-(difference_type n) const{
					iterator_type tmp = _it;
					tmp += n;
					return reverse_iterator(tmp);
				}
				reverse_iterator	&operator--(int){
					reverse_iterator* tmp = this;
					this->_it++;
					return *tmp;
				}
				reverse_iterator	operator--(void){
					return reverse_iterator(_it++);
				}
				pointer				operator->(void) const{
					return &(operator*());
				}
				reference			operator[] (difference_type n){
					return *(_it - n);
				}
				operator	reverse_iterator<const iterator_type>() const{
					//std::cout << "reverse iterator conversion operator" << std::endl;
					return reverse_iterator<const iterator_type>(_it);
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
	template <class Iterator1, class Iterator2>
		bool	operator== (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() == rhs.base();
		}
	template <class Iterator1, class Iterator2>
		bool	operator!= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() != rhs.base();
		}
	template <class Iterator1, class Iterator2>
		bool	operator< (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() >= rhs.base();
		}
	template <class Iterator1, class Iterator2>
		bool	operator<= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() > rhs.base();
		}
	template <class Iterator1, class Iterator2>
		bool	operator> (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() <= rhs.base();
		}
	template <class Iterator1, class Iterator2>
		bool	operator>= (const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs)
		{
			return lhs.base() < rhs.base();
		}
	// namespace ft
}
#endif
