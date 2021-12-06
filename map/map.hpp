#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <stdexcept>
# include <iomanip>
# include <cstddef>
# include <iostream>
# include <memory>
# include <type_traits>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		 class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map{
		public:
			typedef Key			key_type;
			typedef	T			mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type
			typedef Compare			key_compare;
		// value_compare	
			typedef Alloc			allocator_type;
			typedef	value_type&		reference;
			typedef const value_type&	const_reference;
			typedef value_type*		pointer;
			typedef const value_type*	const_pointer;
		// iterators
		// iterator bidirectional_iterator.
		// const iterator
		// reverse iterator
		// const reverse iterator
			typedef ptrdiff_t		difference_type;
			typedef size_t			size_type;
	// PUBLIC MEMBER FUNCTIONS
		// CONSTRUCTOR
			// empty(1)
			explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
			// range(2)
			template <class InputIterator>
				map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type());
			// copy (3)
				map (const map& x);

		// DESTRUCTOR
			~map(void);

		// OEPRATOR=
			map& operator=(const map& obj);

		// ITERATORS
			iterator	begin(void);
			const_iterator 	begin(void) const;
			iterator	end(void);
			const_iterator	end(void) const;
			reverse_iterator	rbegin(void);
			const_reverese_iterator	rbegin(void) const;
			reverse_iterator	rend(void);
			const_reverse_iterator	rend(void) const;

		// CAPACITY
			bool	empty(void) const;
			size_type	size(void) const;
			size_type	max_size(void) const;

		// ELEMENT ACCESS
			mapped_type&	operator[] (const key_type& k);

		// MODIFIERS
			// single elemet (1)
			ft::pair<iterator, bool> insert (const value_type& val);
			// with hint (2)
			iterator	insert (iterator position, const value_type& val);
			// range(3)
			template <class InputIterator>
				void	insert (InputIterator first, InputIterator last);
		// ERASE
			// (1)
			void	erase(iterator position);
			// (2)
			size_type erase (const key_type& k);
			// (3)
			void	erase (iterator first, iterator last);

		// SWAP
			void swap (map& x);

		// CLEAR
			void clear();

		// OBSERVERS
			key_compare	key_comp(void) const;
			value_compare	value_comp(void) const;

		// OPERATIONS
			iterator	find (const key_type& k);
			const_iterator	find (const key_type& k) const;
			size_type	count (const key_type& k) const;
			iterator	lower_bound(const key_type& k);
			const_iterator	lower_bound(const key_type& k) const;
			iterator	upper_bound(const key_type& k);
			const_iterator	upper_bound(const key_type& k) const;
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k)
				const;
			ft::pair<iterator,iterator>	equal_range(const key_type& k);

		// ALLOCATOR
			allocator_type	get_allocator(void) const{
				return _allocator;
			}
		private:
			allocator_type	_allocator;
		};

}

#endif
