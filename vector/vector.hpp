#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEFAULT_CAPACITY 4

# include <iostream>
# include <memory>
# include "iterators.hpp"

template <class T, class Allocator = std::allocator<T> >
class	vector{
	public:
		typedef Allocator	allocator_type;
		typedef T			value_type;
		typedef size_t		size_type;


		explicit vector (const allocator_type& alloc = allocator_type()) : _capacity(DEFAULT_CAPACITY){
			_data = _allocator.allocate(DEFAULT_CAPACITY);
		}
		explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _capacity(n), _size(n){
			_data = _allocator.allocate(_capacity);
			for (int i=0; i<_size; i++){
				_allocator.construct(_data+i, val);
			}
		}
		vector(T *begin, T *end){
			_capacity = end - begin;
			_size = end - begin;
			_data = _allocator.allocate(_size);
			for (int i=0; i < _size; i++){
				_allocator.construct(_data+i, *(begin+i));
			}
		}
		vector (const vector& x){
			*this = x;
		}
		~vector(void){
			if (_size > 0){

				for (int i=_size-1; i >=0; i--){
					_allocator.destroy(_data+i);
				}
			}
			_allocator.deallocate(_data, _size);
		}
		vector &operator=(vector const &rhs){
			if (this != &rhs){
				_size = rhs.size();
				_capacity = rhs.capacity();
				_data = _allocator.allocate(_capacity);
				for (int i=0; i<_size; i++){
					_data[i] = rhs.at(i);
				}
			}
		}

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
			return _allocator.max_size();
		}
		size_t	capacity(void) const{
			return _capacity;
		}
		bool	empty(void) const{
			if (!_size)
				return true;
			return false;
		}
		void	reserve(size_t n);

		void resize (size_type n, value_type val = value_type()){
			if (n < _size){

			}
		}
		void	resize(size_t n){
			if (n < _size){
				T	*tmp = _allocator.allocate(n);
				int i=0;
				for (i; i<n; i++){
					_allocator.construct(tmp+i, _data[i]);
					_allocator.destroy(&_data[i]);
				}
				_allocator.deallocate(_data, _capacity);
				_capacity = n;
				_size = n;
				_data = tmp;
			}
			else if (n > _size){
				
			}
		}

// ELEMENT ACCESS
		T		&operator[](size_t n){
			return _data[n];
		}
		T		&at(size_t idx){
			return _data[idx];
		}
		T		&front(void){
			return _data[_size-1];
		}
		T		&back(void){
			return _data[0];
		}

// MODIFIERS	
		void	assign(size_t n, T const &val);
		void	push_back(T const &val){
			if (_size == _capacity){
				T	*tmp = _allocator.allocate(_capacity * 2);
				for (int i=0; i < _size; i++){
 					 _allocator.construct(tmp+i, _data[i]);
					 _allocator.destroy(_data+i);
				}
				_allocator.deallocate(_data, _capacity);
				_data = tmp;
				_capacity *= 2; 
			}
			_allocator.construct(_data+_size, val);
			_size++;
		}
		void	pop_back(void);
		
// DEBUG

		void	debug(void) const{
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_data" << std::endl;	
			std::cout << "[";
			if (_size > 1){
				for (int i=0; i < _size-1; i++){
					std::cout << _data[i] << ", ";
				}
			}
			if (_size > 0){
				std::cout << _data[_size-1];
			}
			std::cout << "]" << std::endl;
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_size" << std::endl;	
			std::cout << _size << std::endl;
			std::cout << "----------------------------------------" << std::endl;	
			std::cout << "_capacity" << std::endl;	
			std::cout << _capacity << std::endl;
			std::cout << "----------------------------------------" << std::endl;	


		}

	private:
		Allocator	 _allocator;
		T			*_data;
		size_t		 _size;
		size_t		 _capacity;
};

#endif