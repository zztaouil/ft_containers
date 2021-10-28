#ifndef ITERATORS_HPP
# define ITERATORS_HPP

# include <cstddef>
# include <iostream>


template <class T>

class Iterator{
public:
	typedef	 T	 	value_type;
	typedef	 T*	 	pointer;
	typedef	 T const *	const_pointer;
	typedef	 T&	 	reference;
	typedef	ptrdiff_t	distance;

//Is default-constructible, copy-constructible, copy-assignable, destructible i.e (X a; X b(a); b = a;)
	Iterator(void);
	Iterator(Iterator const &obj);
	~Iterator(void);
	Iterator &operator = (pointer addr);
	Iterator &operator = (Iterator const &rhs);
//Can be compared for equivalence using the equality/inequality operators i.e (a == b; a != b;)
	bool operator == (Iterator const &rhs);
	bool operator != (Iterator const &rhs);
//Can be dereferenced as an rvalue i.e (*a; a->m;)
//For mutable iterators (non-constant) i.e (*a = t)
	pointer operator -> (void);
	reference operator * (void);
//Can be incremented i.e (++a, a++, *a++)
	Iterator operator ++ (int);
	Iterator &operator ++ (void);
//Getter for _ptr private member
	const_pointer get_ptr(void) const;
	
private:
	pointer _ptr;
};

template<class T>
Iterator<T>::Iterator(void)
:_ptr(nullptr){}

template<class T>
Iterator<T>::~Iterator(void)
{}

template<class T>
Iterator<T>::Iterator(Iterator const &obj)
{
	*this = obj;
}

template<class T>
Iterator<T> &Iterator<T>::operator=(Iterator const &rhs)
{
	if (this != &rhs){
		this->_ptr = rhs.get_ptr();
	}
	return *this;
}

template<class T>
T const  *Iterator<T>::get_ptr(void) const
{
	return _ptr;
}

template<class T>
T &Iterator<T>::operator * (void)
{
	return *_ptr;
}

template<class T>
T *Iterator<T>::operator -> (void)
{
	return _ptr;
}

template<class T>
Iterator<T> &Iterator<T>::operator = (T *addr)
{
	this->_ptr = addr;
	return *this;
}

template<class T>
bool Iterator<T>::operator == (Iterator<T> const &rhs)
{
	return this->_ptr == rhs.get_ptr();
}

template<class T>
bool Iterator<T>::operator != (Iterator<T> const &rhs)
{
	return this->_ptr != rhs.get_ptr();
}

template<class T>
std::ostream	&operator << (std::ostream &o, Iterator<T> const &obj)
{
	o << "Address: " << obj.get_ptr() << std::endl;
	o << "Value: " << *obj.get_ptr() << std::endl;
	return o;
}
#endif
