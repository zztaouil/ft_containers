#ifndef vector_HPP
# define vector_HPP

# define DEFAULT_CAPACITY 0

# include <string>
# include <stdexcept>
# include <iomanip>
# include <cstddef>
# include <iostream>
# include <memory>
# include <type_traits>
# include "../iterator/random_access_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"
# include "../iterator/equal.hpp"
# include "../iterator/lexico_compare.hpp"
# include "../iterator/enable_if.hpp"
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
			typedef ft::Iterator<value_type> 			iterator;
			typedef ft::Iterator<const value_type> 		const_iterator;
			typedef ft::reverse_iterator<iterator>		reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef size_t					size_type;
			typedef ptrdiff_t				difference_type;

			// Exceptions
			class out_of_range : public std::exception{
				public:
					virtual const char *what(void) const throw(){
						return "out_of_range";
					}
			};
			class emptyvector : public std::exception{
				public:
					virtual const char *what(void) const throw(){
						return "vector_is_empty";
					}
			};
			class failed_construction : public std::exception{
				public:
					virtual const char *what(void) const throw(){
						return "failed_construction";
					}
			};
			// vector::vector
			explicit vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc), _size(DEFAULT_CAPACITY), _capacity(DEFAULT_CAPACITY){
					_data = _allocator.allocate(DEFAULT_CAPACITY);
					(void)alloc;
				}
			explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
				: _allocator(alloc), _size(0), _capacity(n){
//					std::cerr << "vector fill constructor" << std::endl;
					_data = _allocator.allocate(_capacity);
					for (size_type i=0; i<n; i++){
						try{
							_allocator.construct(_data + i, val);
						}catch(...){
//							std::cerr << "exception catched" << std::endl;
							vector_dest_ext();
							throw failed_construction();
						}
						_size++;
					}
					// O(n)	
				}

			template <class InputIterator>
				vector(InputIterator begin, InputIterator end,
						typename ft::enable_if<!std::is_integral<InputIterator>::value, const allocator_type&>::type = allocator_type())
				: _allocator(allocator_type()), _size(0), _capacity(0){
//					std::cerr << "vector range contructor" << std::endl;
					difference_type d = std::distance(begin, end);
					_size = static_cast<size_type>(d);
					_capacity = static_cast<size_type>(d);
					_data = _allocator.allocate(_capacity);
					for(size_type i=0; i<_size; i++){
						_allocator.construct(_data + i, *begin++);
					}
				}
			vector (const vector& x){
				*this = x;
			}
			// ;
			void	vector_dest_ext(void){
				if (_size != 0){
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(_data + i);
					_size = 0;
				}
			}
			// vector::~vector
			~vector(void){
				vector_dest_ext();
				if (_capacity != 0){
					_allocator.deallocate(_data, _capacity);
					_capacity = 0;
				}
			}
			// ;
			vector &operator=(vector const &rhs){
				if (this != &rhs){
					_size = rhs.size();
					_capacity = rhs.capacity();
					_data = _allocator.allocate(_capacity);
					for (size_type i=0; i<_size; i++){
						_allocator.construct(_data + i, rhs[i]);
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
			reverse_iterator			rbegin(void){
				return reverse_iterator(end());
			}
			const_reverse_iterator		rbegin(void) const{
				return const_reverse_iterator(end());
			}
			reverse_iterator			rend(void){
				return reverse_iterator(begin());
			}
			const_reverse_iterator			rend(void) const{
				return const_reverse_iterator(begin());
			}

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
				// This function causes the container to reallocate its storage increasing its capacity to n (or greater)?
				if (n > max_size()){
					// std::cerr << n << " " << max_size() << std::endl;
					throw std::length_error("length_error");
				}
				if (!n){
					_data = _allocator.allocate(1);
					_capacity = 1;
				}
				else if (n > _capacity){
					pointer	tmp = _allocator.allocate(n);
					for (size_type i = 0;i < _size; i++){
						_allocator.construct(tmp + i, _data[i]);
						_allocator.destroy(_data + i);
					}
					if (!_capacity)	
						_allocator.deallocate(_data, _capacity);
					_capacity = n;
					_data = tmp;
				}
			}
			// If n is smaller than the current container size, the content is reduced to its first n elements, destroying those beyond
			// If n is greater than the current container size, the content is expanded by insert at the end as many elements as needed
			//to reach a size of n. if val is specified, the new elements are initialized as copies of val, otherwise, they are
			//value-initialized
			// The function throws length_error if n is greater than max_size.
			// Does it reallocate?
			// Yes in case (n > _capacity)
			void resize (size_type n, value_type val = value_type()){
				if (n > max_size())
					throw std::length_error("length_error");
				else if (n < _size){
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(_data + i);
					_size = n;
				}
				else if (n > _size && n <= _capacity){
					while (_size < n)
					{
						_allocator.construct(_data + _size, val);
						_size++;
					}
				}
				else if (n > _capacity)
				{
					if (n > _capacity * 2)
						reserve(n);
					else
						reserve(2*_capacity);
					while (_size < n){
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
					throw std::out_of_range("out_of_range");
				return _data[n];
			}
			reference	at(size_t n){
				if (n >= _size)
					throw std::out_of_range("out_of_range");
				return _data[n];
			}
			const_reference	front(void) const{				
				if (empty())
					throw emptyvector();
				return _data[0];
			}
			reference	front(void){		
				if (empty())
					throw emptyvector();
				return _data[0];
			}
			const_reference	back(void) const{
				if (empty())
					throw emptyvector();
				return _data[_size - 1];
			}
			reference	back(void){
				if (empty())
					throw emptyvector();		
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
					difference_type d = std::distance(first, last);
					for (size_type i = 0; i <_size; i++)
						_allocator.destroy(_data +i);
					if (static_cast<size_type>(d) > _capacity)
						reserve(d);
					for (size_type i = 0; i < static_cast<size_type>(d); i++)
						_allocator.construct(_data + i, *first++);
					_size = static_cast<size_type>(d);
				}
			// ;
			void	push_back(value_type const &val){
				if (_capacity == 0)
					reserve(1);
				else if (_size == _capacity){
					reserve(_capacity * 2);
				}
				_allocator.construct(_data+_size, val);
				_size++;
			}
			void	pop_back(void){
				_allocator.destroy(_data + _size - 1);
				_size -= 1;
			}
			iterator 	insert (iterator position, value_type const &val){
				difference_type d = std::distance(begin(), position);
				if (_size + 1 > _capacity){
					reserve(_capacity * 2);
				}
				if (static_cast<size_type>(d) == _size){
					try{
						_allocator.construct(_data + _size, val);
						_size++;
					}catch(...){

					}
				}
				else if (static_cast<size_type>(d) < _size){
					for (size_type i = _size; i > static_cast<size_type>(d); i--){
						_allocator.construct(_data + i, _data[i - 1]);
						_allocator.destroy(_data + i - 1);
					}
					try{
						_allocator.construct(_data + d, val);
						_size++;
					}catch(...){}

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
					for (size_type i = _size; i < (_size + n); i++){

						_allocator.construct(_data + i, val);
					}
					_size += n;
				}
				else if (static_cast<size_type>(d) < _size){
					// std::cout << "hna?" << std::endl;
					for (size_type i = _size + n - 1; i >= (static_cast<size_type>(d) + n); i--){
						// std::cout << _data[i-n] << std::endl;
						_allocator.construct(_data + i, _data[i - n]);
					}
					for (size_type i = static_cast<size_type>(d); i < (static_cast<size_type>(d) + n); i++){
						// std::cout << i << std::endl;
						if (i < _size){
							// std::cout << "$" << _data[i] << std::endl;
							_allocator.destroy(_data + i);
						}
						_allocator.construct(_data + i, val);
					}
					// std::cout << "hna!" << std::endl;

					_size += n;
				}
				return ;
			}
			template <class InputIterator>
				void		insert (iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if<!std::is_integral<InputIterator>::value,
						InputIterator>::type = InputIterator()){
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
							_allocator.construct(_data + i - 1, _data[i - l - 1]);
							_allocator.destroy(_data + i - l - 1);
						}
						for (size_type i = static_cast<size_type>(d); i < (static_cast<size_type>(d) + l); i++){
							_allocator.construct(_data + i, *first++);
						}
						_size += l;
					}
					return ;
				}
			// this is fine
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
			// I'm quiet sure that the return isn't working properly
			// not so much!
			// This is quite a pickle
			// Yeah all done
			iterator 	erase(iterator first, iterator last){
				difference_type d = std::distance(begin(), first);
				difference_type l = std::distance(first, last);

				if (static_cast<size_type>(l) == _size)
					clear();
				else if (d + l == static_cast<difference_type>(_size)){
					for (size_type i = static_cast<size_type>(d); i < _size; i++)
						_allocator.destroy(_data + i);
					_size -= l;
				}
				else if (static_cast<size_type>(d + l) < _size){
					for (size_type i = static_cast<size_type>(d); i <= static_cast<size_type>(d + l); i++){
						_allocator.destroy(_data + i);
					}
					for (size_type i = static_cast<size_type>(d + l); i < _size; i++){
						_allocator.construct(_data + i - l, _data[i]);
						_allocator.destroy(_data + i);
					}
					_size -= l;
				}
				return iterator(_data + d);
			}
			void		swap(vector &x){
				std::swap(this->_capacity, x._capacity);
				std::swap(this->_size, x._size);
				std::swap(this->_data, x._data);
			}
			void		clear(){
				for (size_type i=0; i<_size; i++){
					_allocator.destroy(_data+i);
				}
				_size=0;
			}

			allocator_type get_allocator(void) const{
				return _allocator;
			}

			// DEBUG

			void	debug(void) const{
				std::cout << std::setw(40) << std::right << "DEBUG-------------------------------------------------------------------------" 
					<< std::endl;	
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
				std::cout << "------------------------------------------------------------------------------" << std::endl;	
				std::cout << "_size" << std::endl;	
				std::cout << _size << std::endl;
				std::cout << "------------------------------------------------------------------------------" << std::endl;	
				std::cout << "_capacity" << std::endl;	
				std::cout << _capacity << std::endl;
				std::cout << std::setw(40) << "==============================================================================" << std::endl;
			}

		private:
			allocator_type			_allocator;
			pointer				_data;
			size_type			_size;
			size_type			_capacity;
		};
	/*
	 *	a!=b	!(a==b)
	 *	a>b	b<a
	 *	a<=b	!(b<a)
	 *	a>=b	!(a<b)
	 * */
	template < class T, class Alloc>
		bool operator == (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			if (lhs.size() == rhs.size())
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			return false;
		}
	template <class T, class Alloc>
		bool operator != (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			if (lhs.size() == rhs.size())
				return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			return true;
		}
	template <class T, class Alloc>
		bool operator < (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			return ft::lexicographical_compare(lhs.begin(), lhs.end()
					, rhs.begin(), rhs.end());
		}
	template <class T, class Alloc>
		bool operator <= (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			return !ft::lexicographical_compare(rhs.begin(), rhs.end(),
					lhs.begin(), lhs.end());
		}
	template <class T, class Alloc>
		bool operator > (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			return ft::lexicographical_compare(rhs.begin(), rhs.end()
					, lhs.begin(), lhs.end());

		}
	template <class T, class Alloc>
		bool operator >= (const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs){
			return !ft::lexicographical_compare(lhs.begin(), lhs.end(),
					rhs.begin(), rhs.end());
		}
	template <class T, class Alloc>
		void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
		{
			x.swap(y);
		}
}
#endif
