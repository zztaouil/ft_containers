#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <stdexcept>
# include <iomanip>
# include <cstddef>
# include <iostream>
# include <type_traits>
# include <algorithm>
# include "../iterator/bidirectional_iterator.hpp"
# include "../iterator/reverse_iterator.hpp"
# include "../iterator/lexico_compare.hpp"
# include "../iterator/equal.hpp"
# include <vector>
# include "pair.hpp"
# include "AVL.hpp"
# include "../stack/stack.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>,
		 class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map{
		public:


			typedef Key			key_type;
			typedef T			mapped_type;
			typedef ft::pair<const key_type,mapped_type> value_type;
			typedef Compare			key_compare;
			typedef Alloc			allocator_type;
			typedef value_type&		reference;
			typedef const value_type&	const_reference;
			typedef value_type*		pointer;
			typedef const value_type*	const_pointer;
			typedef bidirectional_iterator<value_type, key_compare> iterator;
			typedef bidirectional_iterator<const value_type, key_compare> const_iterator;
			typedef reverse_iterator<const_iterator> const_reverse_iterator;
			typedef reverse_iterator<iterator>		reverse_iterator;
			typedef ptrdiff_t		difference_type;
			typedef size_t			size_type;

			typedef node<value_type>	Node;
			class value_compare : public std::binary_function<value_type, value_type, bool>{
				friend class map;
				protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
				public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
			};
	// PUBLIC MEMBER FUNCTIONS
		// CONSTRUCTOR
			// empty(1)
			explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0){
					(void)comp;
//					std::cout << "Map default constructor" << std::endl;
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
			map& operator=(map const &obj){
				// std::cout << "operator=" << std::endl;
				this->clear();
				this->insert(obj.begin(),obj.end());
				this->_allocator = obj._allocator;
				return *this;
			}

		// ITERATORS
			iterator	begin(void) noexcept{
				// std::cout << "Non const begin" << std::endl;
				Node* curr = _AVL.tree_min(_AVL.root);
				return iterator(&(curr->data), _AVL.root, curr);
			}
			const_iterator	begin(void) const noexcept{
				// std::cout << "const begin" << std::endl;
				Node* curr = _AVL.tree_min(_AVL.root);
				return const_iterator(&(curr->data), reinterpret_cast<node<const value_type>*>(_AVL.root), reinterpret_cast<node<const value_type>*>(curr));
			}
			iterator	end(void) {
				return iterator(0x0, _AVL.root, 0x0);
			}
			const_iterator	end(void) const{
				return const_iterator(0x0, reinterpret_cast<node<const value_type>*>(_AVL.root), 0x0);
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
			mapped_type&	operator[] (const key_type& val){
				 return (*((this->insert(ft::make_pair(val,mapped_type()))).first)).second ;
			}

		// MODIFIERS
			// single elemet (1)
			ft::pair<iterator, bool> insert (const value_type& val){
//				node<value_type>*	ret = _AVL.tree_search(_AVL.root, val);
//				if (ret != NULL)
//					return ft::make_pair<iterator, bool>
//						(iterator(&ret->data, _AVL.root), false);
				pair<Node*,bool> toto = _AVL.insert(&_AVL.root, val);
				if (toto.second != false){
					_size++;
					return ft::make_pair<iterator, bool>(iterator(&toto.first->data, _AVL.root, toto.first), true);
				}
				return ft::make_pair<iterator, bool>(iterator(&toto.first->data, _AVL.root, toto.first), false);
			}
			// with hint (2) i.e pos
			iterator	insert (iterator position, const value_type& val){
				ft::pair<iterator, bool> ret = insert(val);
				return ret.first;
			}
			// range(3)
			template <class InputIterator>
				void	insert (InputIterator first, InputIterator last){
					// std::cout << "HERE" << std::endl;
					while (first != last){
						insert(*first);
						first++;
					}
				}
		// ERASE
			// (1)
			void	erase(iterator position){
				if (position.get_ptr() == 0x0)
					return ;
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
				Node* nd = _AVL.tree_search(
						_AVL.root,
						ft::make_pair(k, mapped_type()));
				if (nd == 0)
					return 0;
				_AVL.tree_delete(
					&_AVL.root,
					nd
					);
				_size--;
				return 1;
			}
			// (3)
			void	erase (iterator first, iterator last){
				// solution khanza imma come back later
				std::vector<iterator> vec;
				while (first != last){
					vec.push_back(first++);
				}
				for (size_t i = 0; i<vec.size(); i++){
					erase(vec[i]);
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
				// std::cout << "Clear: " << _AVL.root->right << " " << _AVL.root->left << std::endl;
				_AVL.root = 0x0;
				_size = 0;
			}

		// OBSERVERS
			key_compare	key_comp(void) const{
				key_compare comp;
				return comp;
			}
			value_compare	value_comp(void) const{
				value_compare comp(key_comp());
				return comp;
			}

		// OPERATIONS
			iterator	find (const key_type& k){
				Node* nd = _AVL.tree_search(_AVL.root, ft::make_pair(k,mapped_type()));
				return iterator(&(nd->data), _AVL.root, nd);
			}
			const_iterator	find (const key_type& k) const{
				Node* nd = _AVL.tree_search(_AVL.root, ft::make_pair(k,mapped_type()));
				return const_iterator(&(nd->data), reinterpret_cast<node<const value_type>*>(_AVL.root), reinterpret_cast<node<const value_type>*>(nd));
			}
			size_type	count (const key_type& k) const{
				iterator it = iterator(&(_AVL.tree_search(_AVL.root, ft::make_pair(k,mapped_type()))->data), _AVL.root, _AVL.root);
				if (it.get_ptr() != 0x0)
					return 1;
				return 0;
			}
			iterator	lower_bound(const key_type& k){
				iterator it = find(k);
				if (it.get_ptr() != 0x0)
					return it;
				Node* succes = _successor(k);
				return iterator(&(succes->data), _AVL.root, succes);
			}
			const_iterator	lower_bound(const key_type& k) const{
				const_iterator cit = find(k);
				if (cit.get_ptr() != 0x0)
					return cit;
				Node* succes = _successor(k);
				return const_iterator(&(succes->data), reinterpret_cast<node<const value_type>*>(_AVL.root), reinterpret_cast<node<const value_type>*>(succes));
			}
			iterator	upper_bound(const key_type& k){
				Node* succes = _successor(k);
				return iterator(&(succes->data), _AVL.root, succes);
			}
			const_iterator	upper_bound(const key_type& k) const{
				Node* succes = _successor(k);
				return const_iterator(&(succes->data), reinterpret_cast<node<const value_type>*>(_AVL.root),reinterpret_cast<node<const value_type>*>(succes));
			}
			ft::pair<const_iterator,const_iterator> equal_range(const key_type& k)
				const{
					return ft::make_pair(lower_bound(k), upper_bound(k));
				}
			ft::pair<iterator,iterator>	equal_range(const key_type& k){
				return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}

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

			Node* _successor( const key_type& key ) const{
                Node * successor = nullptr;
				Node * root = this->_AVL.root;
				while (root != nullptr) {
					if (key_compare()(key, root->data.first)) {
						successor = root;
						root = root->left;
					}
					else if (!key_compare()(key, root->data.first))
						root = root->right;
				}
				return (successor);
            }
		};

	template < class Key, class T>
		bool	operator == (const map<Key, T>& lhs, const map<Key, T>& rhs){
			if (lhs.size() == rhs.size())
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
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
