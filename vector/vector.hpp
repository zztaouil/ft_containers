#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEFAULT_ALLOC_SIZE 4

# include <iostream>
# include <memory>

template <class T, class Allocator = std::allocator<T> >
class	vector{
	public:		
		vector(void);
		vector(size_t n, T val);
		vector(T *begin, T *end){
			_alloc_size = end - begin;
			_len = end - begin;
			std::cout << "_len: " << _len << std::endl;
			_data = _allocator.allocate(_len);
			for (int i=0; i < _len; i++){
				_allocator.construct(_data+i, *(begin+i));
			}
		}
		vector(vector const &rhs);
		~vector(void){
			for (int i=_len-1; i >=0; i--){
				_allocator.destroy(_data+i);
			}
			_allocator.deallocate(_data, _len);
		}
		vector &operator=(vector const &rhs);

//	ITERATORS
		T		*begin(void);
		T		*end(void);
		T		*rbegin(void);
		T		*rend(void);

// CAPACITY
		size_t	size(void) const{

		}
		size_t	max_size(void) const;
		size_t	capacity(void) const;
		bool	empty(void) const;
		void	reserve(size_t n);
		void	resize(size_t n, T val);
		void	resize(size_t n);

// ELEMENT ACCESS
		T		&operator[](size_t n);
		T		&at(size_t idx){
			return _data[idx];
		}
		T		&front(void);
		T		&back(void);

// MODIFIERS	
		void	assign(size_t n, T const &val);
		void	push_back(T const &val);
		void	pop_back(void);
		


	private:
		Allocator	 _allocator;
		T			*_data;
		size_t		 _len;
		size_t		 _alloc_size;
};

#endif