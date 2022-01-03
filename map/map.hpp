#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <stdexcept>
# include <iomanip>
# include <cstddef>
# include <iostream>
# include <memory>
# include <type_traits>
# include <algorithm>
# include "../iterator/bidirectional_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"
# include "../iterator/lexico_compare.hpp"
# include "../iterator/equal.hpp"
# include "pair.hpp"
# include "AVL.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		 class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map{
		public:
			typedef Key			key_type;
			typedef	T			mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type;
			typedef Compare			key_compare;
		// value_compare
			typedef Alloc			allocator_type;
			typedef	value_type&		reference;
			typedef const value_type&	const_reference;
			typedef value_type*		pointer;
			typedef const value_type*	const_pointer;
			typedef bidirectional_iterator<value_type, key_compare>	iterator;
			typedef bidirectional_iterator<const value_type, key_compare> const_iterator;
			typedef reverse_iterator<const_iterator> const_reverse_iterator;
			typedef reverse_iterator<iterator>	reverse_iterator;
			typedef ptrdiff_t		difference_type;
			typedef size_t			size_type;

			typedef node<value_type>	Node;
	// PUBLIC MEMBER FUNCTIONS
		// CONSTRUCTOR
			// empty(1)
			explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0){
					(void)comp;
			}
			// range(2)
			template <class InputIterator>
				map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0){
							while (first != last){
								this->insert(*first++);
							}
							(void)comp;
						}
			// copy (3)
				map (const map& x){
					*this = x;
				}


		// DESTRUCTOR
			~map(void){
				_AVL.tree_free(_AVL.root);
			}

		// OEPRATOR=
			map& operator=(const map& obj){
				if (this != &obj){
					iterator it = obj.begin();
					while (it != obj.end()){
						this->insert(*it++);
					}
				}
				return *this;
			}

		// ITERATORS
			iterator	begin(void) {
				return iterator(&(_AVL.tree_min(_AVL.root)->data), _AVL);
			}
			const_iterator 	begin(void) const{
				return const_iterator(&(_AVL.tree_min(_AVL.root)->data), _AVL);
			}
			iterator	end(void) {
				return iterator(0x0, _AVL);
			}
			const_iterator	end(void) const{
				return const_iterator(0x0, _AVL);
			}
			reverse_iterator	rbegin(void){
				return reverse_iterator(end());
			}
			const_reverse_iterator	rbegin(void) const{
				return const_reverse_iterator(end());
			}
			reverse_iterator	rend(void){
				return reverse_iterator(begin());
			}
			const_reverse_iterator	rend(void) const{
				return const_reverse_iterator(begin());
			}

		// CAPACITY
			bool	empty(void) const{return _size == 0;}
			size_type	size(void) const{ return _size;}
			size_type	max_size(void) const{ return _allocator.max_size();}

		// ELEMENT ACCESS
			mapped_type&	operator[] (const key_type& k){
				Node*	nd = _AVL.tree_search(
						_AVL.root, ft::make_pair(k, mapped_type()));
				if (nd != 0x0)
					return nd->data.second;
				return mapped_type();
			}

		// MODIFIERS
		//	Node*	tree_search(Node* x, Data key){
			// single elemet (1)
			ft::pair<iterator, bool> insert (const value_type& val){
				node<value_type>*	ret = _AVL.tree_search(_AVL.root, val);
				if (ret != NULL)
					return ft::make_pair<iterator, bool>
						(iterator(&ret->data), false);
				_AVL.insert(&_AVL.root, val);
				_size++;
				// if key does not exist is tree i return root
				return ft::make_pair<iterator, bool>(iterator(&((value_type &)val)), true);
			}
			// with hint (2) i.e pos
			iterator	insert (iterator position, const value_type& val);
			// range(3)
			template <class InputIterator>
				void	insert (InputIterator first, InputIterator last){
					while (first != last){
						insert(*first);
						first++;
					}
				}
		// ERASE
			// (1)
			void	erase(iterator position){
				// tree_delete
				_AVL.tree_delete(
						&_AVL.root,
						_AVL.tree_search(
							_AVL.root,
							*position
							)
						);
				_size--;
			}
			// (2)
			size_type erase (const key_type& k){
				_AVL.tree_delete(
					&_AVL.root,
					_AVL.tree_search(
						_AVL.root,
						ft::make_pair(k, mapped_type()))
					);
				_size--;
			}
			// (3)
			void	erase (iterator first, iterator last){
				while (first != last){
					this->erase(first++);
				}
			}

		// SWAP
			void swap (map& x){
				std::swap(this->_AVL, x._AVL);
				std::swap(this->_size, x._size);
			}

		// CLEAR
			void clear(){
				_AVL.tree_free(_AVL.root);
				_size = 0;
			}

		// OBSERVERS
			key_compare	key_comp(void) const{
				key_compare comp;
				return comp;
			}
//			value_compare	value_comp(void) const;

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
		// Debug tree
		void	debug(void){
			_AVL.tree_debug(_AVL.root);
		}
		private:
			tree<value_type, key_compare>	_AVL;
			allocator_type	_allocator;
			size_type	_size;
		};

	template < class Key, class T>
		bool	operator == (const map<Key, T>& lhs, const map<Key, T>& rhs){
			if (lhs.size() == rhs.size())
			 	return ft::equal(lhs.begin(), lhs,end(), rhs.begin());
			return false;
		}

	template < class Key, class T>
		bool	operator != (const map<Key, T>& lhs, const map<Key, T>& rhs){
			if (lhs.size() == rhs.size())
			 	return !ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			return false;
		}

	template < class Key, class T>
		bool	operator < (const map<Key, T>& lhs, const map<Key, T>& rhs){
			return ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end());
		}
	template < class Key, class T>
		bool	operator <= (const map<Key, T>& lhs, const map<Key, T>& rhs){
			return !ft::lexicographical_compare(rhs.begin(), rhs.end(),
			lhs.begin(), lhs.end());
		}

	template < class Key, class T>
		bool	operator > (const map<Key, T>& lhs, const map<Key, T>& rhs){
			return ft::lexicographical_compare(rhs.begin(), rhs.end(),
			lhs.begin(), lhs.end());
		}

	template < class Key, class T>
		bool	operator >= (const map<Key, T>& lhs, const map<Key, T>& rhs){
			return !ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end());
		}

}



#endif
