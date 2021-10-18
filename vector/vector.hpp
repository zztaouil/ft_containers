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
			_size = end - begin;
			_data = _allocator.allocate(_size);
			for (int i=0; i < _size; i++){
				_allocator.construct(_data+i, *(begin+i));
			}
		}
		vector(vector const &rhs);
		~vector(void){
			for (int i=_size-1; i >=0; i--){
				_allocator.destroy(_data+i);
			}
			_allocator.deallocate(_data, _size);
		}
		vector &operator=(vector const &rhs);

//	ITERATORS
		T		*begin(void);
		T		*end(void);
		T		*rbegin(void);
		T		*rend(void);

// CAPACITY
		size_t	size(void) const{
			return _size;
		}
		size_t	max_size(void) const{
			return _alloc_size;
		}
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
		void	push_back(T const &val){
			if (_size == _alloc_size){
				T	*tmp = _allocator.allocate(_alloc_size * 1.62);
				for (int i=0; i < _size; i++){
					_allocator.construct(tmp+i, *(_data+i));
					_allocator.destroy(_data+i);
				}
				_allocator.deallocate(_data, _size);
				_data = tmp;
				_alloc_size *= 1.62; 
			}
			_data[_size++] = val;
		}
		void	pop_back(void);
		
// DEBUG

		void	debug(void) const{
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_data" << std::endl;	
			std::cout << "[";
			for (int i=0; i < _size-1; i++){
				std::cout << _data[i] << ", ";
			}
			std::cout << _data[_size-1] << "]" << std::endl;
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_size" << std::endl;	
			std::cout << _size << std::endl;
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_alloc_size" << std::endl;	
			std::cout << _alloc_size << std::endl;
			std::cout << "----------------------------------------" << std::endl;	


		}

	private:
		Allocator	 _allocator;
		T			*_data;
		size_t		 _size;
		size_t		 _alloc_size;
};

#endif