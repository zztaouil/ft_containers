#ifndef AVL_HPP
# define AVL_HPP

# include "pair.hpp"
# include <iostream>

namespace ft
{
	template <class T>
		struct node{
			T data;
			node* left;
			node* right;
			node* parent;
			// balance factor
			int	bf;
		};
	template <class U, class Alloc = std::allocator<node<U> > >
		struct tree{
			typedef node<U>	Node;
			typedef U	Data;
			typedef Alloc	allocator_type;
//			typedef Compare key_compare;
//			typedef typename Alloc::template rebind<Node>::other
//				allocator_type;

			tree(const allocator_type& alloc = allocator_type())
				:root(0), allocator(alloc){
//					std::cout << "tree constructor" << std::endl;
				}
			~tree(void){
//				std::cout << "tree destructor" << std::endl;
			}
			tree& operator=(tree const &rhs){
				if (this != &rhs){
					root = rhs.root;
				}
				return *this;
			}
//			}
			// construct new node
			Node*	node_new(Data Data, Node* Parent){
				Node* node = allocator.allocate(1);
				node->left = NULL;
				node->right = NULL;
				node->parent = Parent;
				allocator.construct(&node->data, Data);
				node->bf = 0;
				return node;
			}
			// search
			Node*	tree_search(Node* x, Data key){
				if (x == NULL || key.first == x->data.first)
					return x;
				if (key.first < x->data.first)
					return tree_search(x->left , key);
				else
					return tree_search(x->right, key);
			}
			// insertion
			void	insert_ext(Node** Root, Data data){
				Node*	y = NULL;
				Node*	x = *Root;
				while (x != NULL){
					y = x;
					if (data.first < x->data.first)
						x = x->left;
					else
						x = x->right;
				}
				Node* z = node_new(data, y);
				if (y == NULL)
					*Root = z;
				else if (z->data.first < y->data.first)
					y->left = z;
				else
					y->right = z;
			}
			void	insert(Node** Root, Data data){
				insert_ext(Root,data);
				update_bf(*Root);
				rebalance(*Root);
//				std::cerr << "#" << std::endl;
			}
			void	update_bf(Node* Root){
				if (Root == NULL)
					return ;
				update_bf(Root->left);
				Root->bf = tree_height(Root->right) -
					tree_height(Root->left);
				update_bf(Root->right);
			}
			// deletion
			void	tree_delete(Node** T, Node* z){
				if (z == NULL)
						return ;
				tree_delete_ext(T,z);
				update_bf(*T);
				rebalance(*T);
			}
			// can't delete root of tree? why? FIXED
			void	tree_delete_ext(Node** T, Node* z){
				if (z->left == NULL)
					subtree_shift(T, z, z->right);
				else if (z->right == NULL)
					subtree_shift(T, z, z->left);
				else{
					Node* y = tree_successor(z);
					if (y->parent != z){
						subtree_shift(T, y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					subtree_shift(T, z, y);
					y->left = z->left;
					y->left->parent = y;
				}
				allocator.deallocate(z, 1);
			}
			void	subtree_shift(Node** T, Node* u, Node* v){
				if (u->parent == NULL)
					*T = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				if (v != NULL)
					v->parent = u->parent;
			}
			// free the tree in postorder traversal
			void	tree_free(Node* Root){
				if (Root == NULL)
					return ;
				tree_free(Root->left);
				tree_free(Root->right);
				allocator.deallocate(Root, 1);
			}
			// inorder traversal
			void	tree_inorder(Node* Root){
				if (Root == NULL)
					return ;
				tree_inorder(Root->left);
				std::cout << Root->data << std::endl;
				tree_inorder(Root->right);
			}
			// tree maximum
			Node	*tree_max(Node* x){
				while (x->right != NULL)
					x = x->right;
				return x;
			}
			// tree minimum
			Node	*tree_min(Node* x){
				while (x->left != NULL)
					x = x->left;
				return x;
			}
			// tree successor
			Node*	tree_successor(Node* x){
				if (x->right != NULL)
					return tree_min(x->right);
				Node* y = x->parent;
				while (y != NULL && x == y->right){
					x = y;
					y = y->parent;
				}
				return y;
			}
			// tree predecessor
			Node*	tree_predecessor(Node* x){
				if (x->left != NULL)
					return tree_max(x->left);
				Node* y = x->parent;
				while (y != NULL && x == y->left){
					x = y;
					y = y->parent;
				}
				return y;
			}
			// tree height
			size_t	tree_height(Node* x){
				if (x == NULL)
					return 0;
				size_t	left_height = tree_height(x->left);
				size_t	right_height = tree_height(x->right);
				if(left_height > right_height)
					return left_height+1;
				else
					return right_height+1;
			}
			/*======================================================*/
			// REBALANCING
			//  If during a modifying operation the height difference between
			// two child subtrees changes, this may, as long as it is <2, be
			// reflected by an adaption of the balance information at the parent.
			// During insert and delete operations as (temporary) height difference
			// of 2 nay arise, which means that the parent subtree has to be
			// "rebalanced". The given repair tools are the so-called "tree rotations"
			// yep something is broken
			void	rebalance(Node* Root){
				if (Root == NULL)
					return ;

				rebalance(Root->left);
				rebalance(Root->right);
//				std::cerr << Root << " " << Root->data << " " << Root->bf << std::endl;
				if (Root->bf >= 2 && Root->right->bf >= 0){
//					std::cerr << "left rot " << Root->data << " " << Root->right->data << " " << Root->bf << std::endl;
//					return ;
					rotate_left(Root, Root->right);
					return ;
				}
				if (Root->bf <= -2 && Root->left->bf <= 0){
//					std::cerr << "right rot " << Root->data << " " << Root->left->data << std::endl;
//					return ;
					rotate_right(Root, Root->left);
					return ;
				}
				if (Root->bf >= 2 && Root->right->bf <= 0){
					rotate_right(Root->right, Root->right->left);
					rotate_left(Root, Root->right);
					return ;
				}
				if (Root->bf <= -2 && Root->left->bf >= 0){
					rotate_left(Root->left, Root->left->right);
					rotate_right(Root, Root->left);
					return ;
				}
		}
			// rotate left bf +2
			Node*	rotate_left(Node* X, Node* Z){
				Node* papa = X->parent;
				Node* y = Z->left;
				X->right = y;
				if (y != NULL)
					y->parent = X;
				Z->left = X;
				X->parent = Z;
				Z->parent = papa;
				if (papa == NULL)
					this->root = Z;
				// Questionable? this is a special case.
				// if papa->right == X
				// if papa->left == X
//				std::cerr << "Yes, " << (papa->right == X) << " " << (papa->left == X) << std::endl;
				if (papa  && papa->right == X)
					papa->right = Z;
				if (papa && papa->left == X)
					papa->left = Z;
				Z->bf = tree_height(Z->right) -
					tree_height(Z->left);
				X->bf = tree_height(X->right) -
					tree_height(X->left);
//				if (Z->bf == 0){
//					X->bf = 1;
//					Z->bf = -1;
//				}else{
//					X->bf = 0;
//					Z->bf = 0;
//				}
				return Z;
				// parent of X right node should be pointing to Z;
				// X should be replaced by Z in root node.
			}
			// have to take a closer look into this!
			// not sure if it's working as intended :3
			// rotate right bf -2
			Node*	rotate_right(Node* X, Node* Z)
			{
				Node* papa = X->parent;
				Node* t23 = Z->right;
				X->left = t23;
				if (t23 != NULL)
					t23->parent = X;
				Z->right = X;
				X->parent = Z;
				Z->parent = papa;
				if (papa == NULL)
					this->root = Z;
				if (papa && papa->right == X)
					papa->right = Z;
				if (papa && papa->left == X)
					papa->left = Z;
				Z->bf = tree_height(Z->right) -
					tree_height(Z->left);
				X->bf = tree_height(X->right) -
					tree_height(X->left);
//				if (Z->bf == 0){
//					X->bf = 1;
//					Z->bf = -1;
//				}else{
//					X->bf = 0;
//					Z->bf = 0;
//				}
				return Z;
			}
			/*======================================================*/
			// debug tree
			void	tree_debug(const std::string &prefix,
					const Node* node, bool isLeft){
				if(node != NULL)
				{
					std::cout << prefix;
					std::cout << (isLeft?"├──" : "└──");
					std::cout << "|" << node->data << ":" << node->bf << std::endl;

					tree_debug(prefix+(isLeft?"│   "
								: "    "),
							node->left, true);
					tree_debug(prefix+(isLeft?"│   "
								: "    "),
							node->right, false);
				}
			}
			void	tree_debug(const Node* root){
				std::cout << std::endl;
				tree_debug("$", root, false);
			}
			// root node
			Node*	root;
			// allocator
			allocator_type	allocator;
		};
}

#endif
