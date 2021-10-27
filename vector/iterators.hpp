#ifndef ITERATORS_HPP
# define ITERATORS_HPP

template <class T>

class Iterator{
	public:
		Iterator(void);
		Iterator(Iterator const &obj);
		~Iterator(void);
		Iterator &operator=(Iterator const &rhs);
		
	private:
		T	*_d;
};


#endif
