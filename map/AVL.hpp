#ifndef AVL_HPP
# define AVL_HPP

# define ABS(n) ((n<0)?(-n):(n))
# include "pair.hpp"
# include <memory>
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
			int		bf;
			size_t  height;
			node (const node & obj){
				data = obj.data;
				left = obj.left;
				right = obj.right;
				parent = obj.parent;
				bf = obj.bf;
				height = obj.height;
				return *this;
			}
			operator node<const T>() const{
				return node<const T>();
			}
		};
	template <class U, class Compare, class Alloc = std::allocator<U> >
		class tree{
		public:
			typedef node<U>	Node;
			typedef U	Data;
			typedef Alloc	allocator_type1;
			typedef Compare key_compare;

			// not working on my computer
//			typedef typename allocator_type1::template rebind<Node>::other allocator_type2;
			// hotfix
			typedef std::allocator<Node> allocator_type2;

//
//


			tree(const allocator_type1& alloc = allocator_type1())
				:allocator1(alloc), allocator2(allocator_type2()), root(0), comp(){
//					std::cout << "Tree constructor" << std::endl;
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
//			utility
			size_t	max(size_t a, size_t b){
				return (a<b ? b : a);
			}
			size_t	height(Node* node){
				if (node == NULL)
					return 0;
				return node->height;
			}
			int		BF(Node* node){
				return height(node->right) - height(node->left);
			}
			// construct new node
			Node*	node_new(Data Data, Node* Parent){
				Node* node = allocator2.allocate(1);
				node->left = NULL;
				node->right = NULL;
				node->parent = Parent;
				allocator1.construct(&node->data, Data);
				node->bf = 0;
				node->height = 1;
				return node;
			}
			// search
			Node*	tree_search(Node* x, Data key) const{
				if (x == NULL || key.first == x->data.first)
					return x;
				if (comp(key.first, x->data.first))
					return tree_search(x->left , key);
				else
					return tree_search(x->right, key);
			}
			// insertion
			pair<Node*,bool>	insert_ext(Node** Root, Data data){
				Node*	y = NULL;
				Node*	x = *Root;
				int ht = 0;
				while (x != NULL){
					y = x;
					if (comp(data.first, x->data.first))
						x = x->left;
					else if (data.first == x->data.first)
						return ft::make_pair(x, false);
					else
						x = x->right;
					ht++;
				}
				Node* z = node_new(data, y);
				if (y == NULL){
					*Root = z;
				}
				else if (comp(z->data.first, y->data.first)){
					y->left = z;
				}
				else{
					y->right = z;
				}
				// but first update the parent of the newly inserted node
				// then
				// retrace from it to root in order to update the balance factor
				//  by substraction the right child bf from left child bf
				if (y != NULL){
                    Node *m = y;
					int nb = 0;
					while (m != NULL) {
						m->height = max(height(m->right), height(m->left)) + 1;
						m->bf = BF(m);
						nb = rebalance(m);
						int iter = 0;
						while (iter < nb){
							m = m->parent;
							iter++;
						}
                    	m = m->parent;
                    }
                }
                return ft::make_pair(z, true);
				
			}
			pair<Node*,bool>	insert(Node** Root, Data data){
				pair<Node*,bool>	bobo = insert_ext(Root,data);
				return bobo;
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
				allocator1.destroy(&z->data);
				allocator2.deallocate(z, 1);
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
				allocator1.destroy(&Root->data);
				allocator2.deallocate(Root, 1);
				Root = 0x0;
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
			Node	*tree_min(Node* x) const{
				if (x == NULL)
					return x;
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
			int	rebalance(Node* Root){
				// if (Root == NULL)
				// 	return ;

				// rebalance(Root->left);
				// rebalance(Root->right);
//				std::cerr << Root << " " << Root->data << " " << Root->bf << std::endl;
				// std::cout << "Call to rebalance with bf=" << Root->bf ; 
				if (Root->bf == 2 && Root->right->bf >= 0){
//					std::cerr << "left rot " << Root->data << " " << Root->right->data << " " << Root->bf << std::endl;
					rotate_left(Root, Root->right);
					return 1;
				}
				else if (Root->bf == -2 && Root->left->bf <= 0){
//					std::cerr << "right rot " << Root->data << " " << Root->left->data << std::endl;
					rotate_right(Root, Root->left);
					return 1;
				}
				else if (Root->bf == 2 && Root->right->bf <= 0){
					rotate_right(Root->right, Root->right->left);
					rotate_left(Root, Root->right);
					return 2;
				}
				else if (Root->bf == -2 && Root->left->bf >= 0){
					rotate_left(Root->left, Root->left->right);
					rotate_right(Root, Root->left);
					return 2;
				}
				return 0;
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

				X->height = max(height(X->right), height(X->left)) + 1;
				Z->height = max(height(Z->right), height(Z->left)) + 1;
				X->bf = BF(X);
				Z->bf = BF(X);
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
				X->height = max(height(X->right), height(X->left)) + 1;
				Z->height = max(height(Z->right), height(Z->left)) + 1;

				X->bf = BF(X);
				Z->bf = BF(X);
				// Z->bf = tree_height(Z->right) -
				// 	tree_height(Z->left);
				// X->bf = tree_height(X->right) -
				// 	tree_height(X->left);
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
					std::cout << "|" << node->data << ":" << node->height << std::endl;

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
			// allocators
			allocator_type1 allocator1;
			allocator_type2	allocator2;
			// key_compare
			key_compare	comp;
		};
}

#endif
