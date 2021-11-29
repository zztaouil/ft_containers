#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
		struct pair{
			typedef T1 first_type;
			typedef T2 second_type;
			pair(void) : first(0), second(0){}
			template <class U, class V>
				pair (const pair<U,V>& pr){
					*this = pr;
				}
			pair (const first_type& a, const second_type &b)
			: first(a), second(b){}
			pair& operator= (const pair& pr){
				if (this != &pr){
					first = pr.first;
					second = pr.second;
				}
				return *this;
			}
			first_type	first;
			second_type	second;
		};
	template<class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
			return lhs.first==rhs.first && lhs.second==rhs.second;
		}
}
#endif
