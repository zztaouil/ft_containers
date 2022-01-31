#ifndef STACK_HPP
# define STACK_HPP

# include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
		class stack{
			public:
				typedef	T		value_type;
				typedef Container	container_type;
				typedef	size_t		size_type;

// Constructors
//				stack(void){}
				explicit stack(const container_type& ctnr = container_type()) : _u_container(ctnr){}
				~stack(void){}
// empty method
				bool	empty(void) const{
					return _u_container.empty();
				}
// size method
				size_type	size(void) const{
					return _u_container.size();
				}
// top method
				value_type&	top(void){
					return _u_container.back();
				}
				const value_type&	top(void) const{
					return _u_container.back();
				}
// push method
				void	push(const value_type& val){
					_u_container.push_back(val);
				}
// pop method
 				void	pop(void){
					_u_container.pop_back();
 				}
				friend bool operator== (const stack& lhs, const stack& rhs){ return lhs._u_container == rhs._u_container; }
				friend bool operator!= (const stack& lhs, const stack& rhs){ return lhs._u_container != rhs._u_container; }
				friend bool operator< (const stack& lhs, const stack& rhs){ return lhs._u_container < rhs._u_container; }
				friend bool operator<= (const stack& lhs, const stack& rhs){ return lhs._u_container <= rhs._u_container; }
				friend bool operator> (const stack& lhs, const stack& rhs){ return lhs._u_container > rhs._u_container; }
				friend bool operator>= (const stack& lhs, const stack& rhs){ return lhs._u_container >= rhs._u_container; }

			private:
				container_type		_u_container;
		};
}
#endif
