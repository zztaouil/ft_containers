#ifndef VECTOR_HPP
# define VECTOR_HPP

# define DEFAULT_CAPACITY 0

# include <iomanip>
# include <cstddef>
# include <iostream>
# include <memory>
# include <type_traits>
# include "../iterator/iterators.hpp"
//# include "../iterator/enable_if.hpp"

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
							return "out_of_range";
						}
				};

				// vector::vector
				explicit vector (const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(DEFAULT_CAPACITY), _capacity(DEFAULT_CAPACITY){
					_data = _allocator.allocate(DEFAULT_CAPACITY);
					(void)alloc;
				}
				//_allocator(alloc)
				explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
					: _allocator(alloc), _size(n), _capacity(n){
						_data = _allocator.allocate(_capacity);
						for (size_type i=0; i<_size; i++){
							_allocator.construct(_data + i, val);
						}
						// O(n)	
					}
				// C++ feature
				//typename enable_if<!is_integral<InputIterator>::value,InputIterator >::type = InputIterator())
				template <class InputIterator>
				vector(InputIterator begin, InputIterator end, const allocator_type &alloc = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator >::type = InputIterator())
					: _allocator(alloc), _size(end - begin), _capacity(_size){
						_data = _allocator.allocate(_capacity);
						for (size_type i=0; i < _size; i++){
							_allocator.construct(_data + i, *begin++);
						}
					}
				vector (const vector& x){
					*this = x;
				}
				// ;

				// vector::~vector
				~vector(void){
					if (_size > 0)
						_allocator.destroy(_data);
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
							_allocator.construct(_data + i, rhs.at(i));
						}
					}
					return *this;
				}


				//	ITERATORS
				const_iterator		begin() const{
					return const_iterator(_data);
				}
				iterator		begin(void){
					return iterator(_data);
				}
				const_iterator		end(void) const{
					return const_iterator(_data + _size);
				}
				iterator		end(void){
					return iterator(_data + _size);
				}
				iterator		rbegin(void);
				iterator		rend(void);

				// CAPACITY
				size_type	size(void) const{
					return _size;
				}
				size_type	max_size(void) const{
					return _allocator.max_size();
				}
				size_type	capacity(void) const{
					return _capacity;
				}
				bool	empty(void) const{
					if (!_size)
						return true;
					return false;
				}
				// This function has no effect on the vector size and cannot alter its elements.
				void	reserve(size_type n){
					// This function causes the container to reallocate its storage increasing its capacity to n (or greater)
					if (n > _capacity){
						pointer	tmp = _allocator.allocate(n);
						for (size_type i = 0;i < _size; i++){
							_allocator.construct(tmp + i, _data[i]);
							_allocator.destroy(_data + i);
						}
						_allocator.deallocate(_data, _capacity);
						_capacity = n;
						_data = tmp;
					}
				}
				// If n is smaller than the current container size, the content is reduced to its first n elements, destroying those beyond
				// If n is greater than the current container size, the content is expanded by insert at the end as many elements as needed
				//to reach a size of n. if val is specified, the new elements are initialized as copies of val, otherwise, they are
				//value-initialized
				void resize (size_type n, value_type val = value_type()){
					if (n < _capacity){
						pointer tmp = _allocator.allocate(n);
						size_type i = 0;
						for (; i < n; i++){
							_allocator.construct(tmp + i, _data[i]);
							_allocator.destroy(_data + i);
						}
						for (; i < _size; i++)
							_allocator.destroy(_data + i);
						_allocator.deallocate(_data, _capacity);
						_capacity = n;
						_size = n;
						_data = tmp;
					}
					else{
						reserve(n);
						while (_size < n)
						{
							_allocator.construct(_data + _size, val);
							_size++;
						}
					}
				}

				// ELEMENT ACCESS
				//
				// exception protecti invalid input! check if n is valid.
				const_reference	operator[](size_t n) const{
					return _data[n];
				}
				reference	operator[](size_t n){
					return _data[n];
				}
				const_reference	at(size_t n) const{
					if (n >= _size)
						throw outOfRangeException();
					return _data[n];
				}
				reference	at(size_t n){
					if (n >= _size)
						throw outOfRangeException();
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
				// vector::assign
				void	assign(size_type n,const value_type &val){
					for (size_type i=0; i < _size; i++)
						_allocator.destroy(_data + i);
					_size = 0;
					if ( n > _capacity){
						reserve(n);
					}
					for (; _size<n; _size++)
						_allocator.construct(_data + _size, val);
				}
				template <class InputIterator>
					void	assign(InputIterator first,InputIterator last){
						size_type len = last - first;
						_size = 0;
						if (len > _capacity){
							reserve(len);
						}
						for (size_type i = 0; i < _size; i++)
							_allocator.destroy(_data + i);
						for (size_type i = 0; i < len; i++)
							_allocator.construct(_data + i, first[i]);
						_size = len;
					}
				// ;
				void	push_back(value_type const &val){
					if (_size == _capacity){
						reserve(_capacity * 2);
					}
					_allocator.construct(_data+_size, val);
					_size++;
				}
				void	pop_back(void){
					_allocator.destroy(_data[_size - 1]);
					_size -= 1;
				}
				iterator 	insert (iterator position, value_type const &val){
					difference_type d = std::distance(begin(), position);
					if (_size + 1 > _capacity){
						reserve(_capacity * 2);
					}
					if (static_cast<size_type>(d) == _size)
						_data[_size++] = val;
					else if (static_cast<size_type>(d) < _size){
						for (size_type i = _size; i > static_cast<size_type>(d); i--){
							_allocator.construct(_data + i, _data[i - 1]);
							_allocator.destroy(_data + i - 1);
						}
						_allocator.construct(_data + d, val);
						_size++;
					}
					return iterator(_data + d);
					// O(n)
				}
				void		insert(iterator position, size_type n, value_type const &val){
					difference_type d = std::distance(begin(), position);
					if (n + _size > _capacity)
					{
						if (n + _size > _capacity * 2)
							reserve(n + _size);
						else
							reserve(_capacity * 2);
					}
					if (static_cast<size_type>(d) == _size){
						for (size_type i = _size; i < (_size + n); i++)
							_allocator.construct(_data + i, val);
						_size += n;
					}
					else if (static_cast<size_type>(d) < _size){
						for (size_type i = _size + n - 1; i >= (static_cast<size_type>(d) + n); i--){
							//std::cout << _data[i] << std::endl;
							_allocator.construct(_data + i, _data[i - n]);
						}
						for (size_type i = static_cast<size_type>(d); i < (static_cast<size_type>(d) + n); i++){
							_allocator.destroy(_data + i);
							_allocator.construct(_data + i, val);
						}
						_size += n;
					}
				}
				template <class InputIterator>
					void		insert (iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()){
						difference_type d = std::distance(begin(), position);
						difference_type l = std::distance(first, last);
						if (l + _size > _capacity)
						{
							if (l + _size > _capacity * 2)
								reserve(l + _size);
							else
								reserve(_capacity * 2);
						}
						if (static_cast<size_type>(d) == _size){
							for (size_type i = _size; i < _size + l; i++){
								_allocator.construct(_data + i, *first++);
							}
							_size += l;
						}
						else if (static_cast<size_type>(d) < _size){
							for (size_type i = _size + l; i >= (static_cast<size_type>(d) + l); i--){
								_allocator.construct(_data + i, _data[i - l]);
							}
							for (size_type i = static_cast<size_type>(d); i < (static_cast<size_type>(d) + l); i++){
								_allocator.destroy(_data + i);
								_allocator.construct(_data + i, *first++);
							}
							_size += l;
						}
					}
				iterator 	erase(iterator position){
					difference_type d = std::distance(begin(), position);
					if (static_cast<size_type>(d) == _size - 1){
						_allocator.destroy(_data + _size - 1);
						_size--;
					}
					else if (static_cast<size_type>(d) < _size){
						_size--;
						for (size_type i = static_cast<size_type>(d); i < _size; i++){
							_allocator.destroy(_data + i);
							_allocator.construct(_data + i, _data[i + 1]);
						}
						_allocator.destroy(_data + _size);
					}
					return iterator(_data + d);
				}
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
					std::cout << std::setw(40) << std::right << "---------------------DEBUGG--------------" << std::endl;	
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
				value_type			*_data;
				size_type			_size;
				size_type			_capacity;
		};
}
#endif
