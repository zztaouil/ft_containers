#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEFAULT_CAPACITY 4

# include <iomanip>
# include <cstddef>
# include <iostream>
# include <memory>
# include "../iterator/iterators.hpp"

namespace ft{
	template <class T, class Allocator = std::allocator<T> >
		class	vector{
			public:
				typedef T					value_type;
				typedef Allocator				allocator_type;
				typedef typename allocator_type::reference 	reference;
				typedef typename allocator_type::const_reference const_reference;
				typedef typename allocator_type::pointer 	pointer;
				typedef typename allocator_type::const_pointer 	const_pointer;	
				typedef Iterator<value_type> 			iterator;
				typedef Iterator<const value_type> 		const_iterator;
				typedef size_t					size_type;
				typedef ptrdiff_t				difference_type;

				// Exceptions
				class outOfRangeException : public std::exception{
					public:
						virtual const char *what(void) const throw(){
							return "position out of range";
						}
				};

// vector::vector
				explicit vector (const allocator_type& alloc = allocator_type()) : _capacity(DEFAULT_CAPACITY){
					_data = _allocator.allocate(DEFAULT_CAPACITY);
					(void)alloc;
				}
				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
						: _size(n), _capacity(n){
					_data = _allocator.allocate(_capacity);
					_allocator.construct(_data);
					for (size_type i=0; i<_size; i++){
						_data[i] = val;
					}
					(void)alloc;				
				}
				vector(iterator begin, iterator end){
					_capacity = end - begin;
					_data = _allocator.allocate(_capacity);
					_size = _capacity;
					_allocator.construct(_data);
					for (size_type i=0; i < _size; i++){
						_data[i] = begin[i];
					}
				}
				vector (const vector& x){
					*this = x;
				}
// ;

// vector::~vector
				~vector(void){
					if (_capacity > 0)
						_allocator.deallocate(_data, _capacity);
				}
// ;
				vector &operator=(vector const &rhs){
					if (this != &rhs){
						_size = rhs.size();
						_capacity = rhs.capacity();
						_data = _allocator.allocate(_capacity);
						for (size_type i=0; i<_size; i++){
							_data[i] = rhs.at(i);
						}
					}
					return *this;
				}

// vector::assign
				void	assign(size_t n,const value_type &val){
					_allocator.destroy(_data);
					_size = 0;
					if ( n > _capacity){
						_allocator.deallocate(_data, _capacity);
						_capacity = 0;
						_data = _allocator.allocate(n);
						_capacity=n;
					}
					_allocator.construct(_data);
					for (size_type i=0; i<n; i++)
						_data[_size++] = val;
				}
				template <class InputIterator>
				void	assign(InputIterator first,InputIterator last){
					size_type len = last - first;
					_allocator.destroy(_data);
					_size = 0;
					if (len > _capacity){
						_allocator.deallocate(_data, _capacity);
						_capacity = 0;
						_data = _allocator.allocate(len);
						_capacity = len;

					}
					_allocator.construct(_data);
					for (iterator it = first; it != last; it++)
						_data[_size++] = *it;
				}
// ;
	
				//	ITERATORS
				iterator		begin(void){
					return iterator(_data);
				}
				iterator		end(void){
					return iterator(_data + _size);
				}
				iterator		rbegin(void);
				iterator		rend(void);

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
				void	reserve(size_type n){
					if (n > _capacity){
						pointer	tmp = _allocator.allocate(n);
						for (int i=0;i < _size; i++){
							_allocator.construct(tmp+i, _data[i]);
							_allocator.destroy(_data + i);
						}
						_allocator.deallocate(_data, _capacity);
						_capacity = n;
						_data = tmp;
					}
				}

				void resize (size_type n, value_type val = value_type()){
					if (n < _size){
						pointer tmp = _allocator.allocate(n);
						for (size_type i=0; i<n; i++){
							_allocator.construct(tmp+i, _data[i]);
							_allocator.destroy(&_data[i]);
						}
						_allocator.deallocate(_data, _capacity);
						_capacity = n;
						_size = n;
						_data = tmp;
					}
					else if (n > _size){
						pointer tmp = _allocator.allocate(n);
						size_type i=0;
						while (i < _size){
							_allocator.construct(tmp+i, _data[i]);
							_allocator.destroy(_data+i);
							i++;
						}
						_allocator.deallocate(_data, _capacity);
						_capacity = n;
						_size = n;
						if (!val){
							while (i < n)
							{
								_allocator.construct(tmp+i, NULL);
								i++;
							}
						}else{
							while (i < n)
							{
								_allocator.construct(tmp+i, val);
								i++;
							}
						}
						_data = tmp;
					}
				}

				// ELEMENT ACCESS
				//
				// exception protecti invalid input! check if n is valid.
				const_reference	operator[](size_t n) const{
					try{
						if (n >= _size)
							throw outOfRangeException();
					}catch (outOfRangeException &e){
						std::cout << "operator[]:" << '\n';
						std::cout << e.what() << std::endl;
					}
					return _data[n];
				}
				reference	operator[](size_t n){
					try{
						if (n >= _size)
							throw outOfRangeException();
					}catch (outOfRangeException &e){
						std::cout << "operator[]:" << '\n';
						std::cout << e.what() << std::endl;
					}
					return _data[n];
				}
				const_reference	at(size_t n) const{
					try{
						if (n >= _size)
							throw outOfRangeException();
					}catch (outOfRangeException &e){
						std::cout << e.what() << '\n';
					}
					return _data[n];
				}
				reference	at(size_t n){
					try{
						if (n >= _size)
							throw outOfRangeException();
					}catch (outOfRangeException &e){
						std::cout << e.what() << '\n';
					}
					return _data[n];
				}
				const_reference	front(void) const{				
					return _data[0];
				}
				reference	front(void){		
					return _data[0];
				}
				const_reference	back(void) const{				
					return _data[_size - 1];
				}
				reference	back(void){				
					return _data[_size - 1];
				}

				// MODIFIERS
				// construct and destroy data array not every element.
				void	push_back(value_type const &val){
					if (_size == _capacity){
						pointer	tmp = _allocator.allocate(_capacity * 2);
						for (size_type i=0; i < _size; i++){
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
				void	pop_back(void){
					_allocator.destroy(_data[_size - 1]);
					_size -= 1;
				}
				iterator 	insert (iterator position, value_type const &val){
					size_type idx = position - begin();
					if (idx == _size)
						_data[_size++] = val;
					else{
						std::cout << idx << std::endl;
					}
					return position;
				}
				void		insert(iterator position, size_type n, value_type const &val);
				template <class InputIterator>
				void		insert (iterator position, iterator first, iterator list);
				iterator 	erase(iterator position);
				iterator 	erase(iterator first, iterator last);
				void		swap(vector &x);
				void		clear(){
					for (size_type i=0; i<_size; i++){
						_allocator.destroy(_data+i);
					}
					_allocator.deallocate(_data, _capacity);
					_size=0;
					_capacity=0;
				}
				
				// DEBUG

				void	debug(void) const{
					std::cout << std::setw(40) << "---------------------DEBUGG--------------" << std::endl;	
					std::cout << "_data" << std::endl;	
					std::cout << "[";
					if (_size > 1){
						for (size_type i=0; i < _size-1; i++){
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
					std::cout << std::setw(40) << "----------------------------------------" << std::endl;	


				}

			private:
				allocator_type		_allocator;
				value_type		*_data;
				size_type			_size;
				size_type			_capacity;
		};
}
#endif
