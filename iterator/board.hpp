#include <iterator>
#include <iostream>

/*
	std::iterator is the base class provided to simplify definitions of the required
	types of iterators.

	Template parameters:
	- Category: the category of the iterator.
	- T: the type of the values that can be obtained by derefencing the iterator.
	this type should be void for output iterators.
	- Distance: a type that can be used to identify distance betweem iterators/
	- Pointer: defines a pointer to type iterated over (T)
	- Reference: defines a reference to type iterated over (T)
*/
namespace ft
{
	template < class T>
	class iterator: public std::iterator <std::input_iterator_tag, int>{
	private:
		pointer	_ptr;

	public:
		iterator(pointer ptr): _ptr(ptr){}
		iterator(void) : _ptr(NULL){}
		~iterator(void){}
		iterator(iterator const &obj){
			*this = obj;
		}
		iterator &operator = (iterator const &rhs){
			if (this != &rhs){
				this->_ptr = rhs.get_ptr();
			}
			return *this;
		}

		bool operator != (iterator const &rhs){
			return _ptr != rhs.get_ptr();
		}

		iterator operator ++ (int){
			this->_ptr++;
			return *this;
		}

		pointer get_ptr(void) const{
			return _ptr;
		}
	};
}