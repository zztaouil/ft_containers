#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include <iterator>
# include "../map/AVL.hpp"
// need access to my Tree inside this class.
namespace ft
{
	template <class T>
		class bidirectional_iterator : public std::iterator<std::bidirectional_iterator_tag, T>{
		public:
			// member types
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef T value_type;
			typedef ptrdiff_t	difference_type;
			typedef T*		pointer;
			typedef T&		reference;
			typedef tree<value_type>	Tree;
			typedef typename Tree::Node	Node;
		// default constructor
		bidirectional_iterator(void) : _ptr(0), _myTree(0){};
		// copy constructor
		bidirectional_iterator(bidirectional_iterator const &obj){
			*this = obj;
		}
		// parametric constructor takes a pointer
		bidirectional_iterator(pointer ptr) :
			_ptr(ptr){}
		// parametric constructor takes both a pointer and atree
		bidirectional_iterator(pointer ptr, Tree const &tree) :
			_ptr(ptr), _myTree(tree){}
		// assignement overload
		bidirectional_iterator&	operator=(bidirectional_iterator const&
				rhs){
			if (this != &rhs){
				// shallow copy, imma test later.
				this->_ptr = rhs._ptr;
				this->_myTree = rhs._myTree;
			}
			return *this;
		}
		// destructor
		~bidirectional_iterator(void){}
		// rvalue dereference operators * and ->
		pointer	operator ->(void){return _ptr;}
		reference operator *(void){return *_ptr;}
		
		// increment
		bidirectional_iterator	operator++(int){
			bidirectional_iterator tmp = *this;
			Node* successor = _myTree.tree_successor(
					_myTree.tree_search(
						_myTree.root, *_ptr));
			if (successor != NULL)
				_ptr = &(successor->data);			
			else
				_ptr = 0x0;
			return tmp;
		}
		bidirectional_iterator	operator++(void){
			Node* successor = _myTree.tree_successor(
					_myTree.tree_search(
						_myTree.root, *_ptr));
			if (successor != NULL)
				_ptr = &(successor->data);			
			else
				_ptr = 0x0;
			return *this;
		}
		// decrement
		bidirectional_iterator operator--(int){
			bidirectional_iterator tmp = *this;
			Node* predecessor = _myTree.tree_predecessor(
				_myTree.tree_search(
					_myTree.root, *_ptr)
					);
			if (_ptr == 0x0){
				std::cout << "iterator -> 0x0" << std::endl;
				_ptr = &(_myTree.tree_max(_myTree.root)->data);
			}
			else if (predecessor != NULL)
				_ptr = &(predecessor->data);
			else
				_ptr = 0x0;
			return tmp;
		}
		bidirectional_iterator operator--(void){
			Node* predecessor = _myTree.tree_predecessor(
				_myTree.tree_search(
					_myTree.root, *_ptr)
					);
			if (_ptr == 0x0){
				std::cout << "iterator -> 0x0" << std::endl;
				_ptr = &(_myTree.tree_max(_myTree.root)->data);
			}
			else if (predecessor != NULL)
				_ptr = &(predecessor->data);
			else
				_ptr = 0x0;
			return *this;
		}
		// Conversion operator
		operator bidirectional_iterator<const T>() const{
			return bidirectional_iterator<const T>(_ptr);
		}
		pointer get_ptr(void){ return _ptr;}
		void	set_Tree(Tree const &tr){
			_myTree = tr;
		}
		private:
			pointer	_ptr;
			Tree	_myTree;
		};
	// Non member overloads
	// comparison
	template <class T1, class T2>
		bool	operator==(bidirectional_iterator<T1> lhs,
				bidirectional_iterator<T2> rhs){
			return lhs.get_ptr() == rhs.get_ptr();
		}
	template <class T1, class T2>
		bool	operator!=(bidirectional_iterator<T1> lhs,
				bidirectional_iterator<T2> rhs){
			return lhs.get_ptr() != rhs.get_ptr();
		}

}
#endif
