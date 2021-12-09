#ifndef AVL_HPP
# define AVL_HPP

# include "pair.hpp"
# include <iostream>

// DEFINITION
// 	BALANCE FACTOR:
// 	In a binary tree the balance factor of a node X is defined to be the
// 	height difference of its two child sub-trees.
// 	BF(X) := Height(RightSubtree(X)) - Height(LeftSubtree(X))
//	A binary tree is defined to be an AVL tree if the invariant BF(X)
//	is in included in {-1,0,1} holds for every node X in the tree.
//	A node X with BF(X) < 0 is called "left heavy", one with BF(X) > 0
//	is called "right heavy", and one with BF(X) = 0 is called "balanced"
//
//	PROPERTIES:
//	Balance factors can be kept up-to-date by knowing the previous balance
//	factors and the change in height; it is not necessary to know the
//	absolute height. For holding the AVL balance information, two bits
//	per node are sufficent.
//	The height h (counted as the maximal number of levels) of an AVL tree
//	with n nodes lies in the interval:
//		* where Phi is the golden ration (1+sqrt(5))/2 == 1.618
//		and b = (log2(5)/2log2(Phi))-2 == -0.3277
//		log2(n + 1) <= h < logPhi(n + 2) + b
//	This is because an AVL tree of height h contains at least
//	F(h+2) - 1 nodes where Fn is the fibonacci sequence with the seed values
//	F1 = F2 = 1. (didn't quite fully understand this. i'll come back later)
//
// OPERATIONS
// Read-only operations of an AVL tree involve carrying out the same actions
// as would be carried out on an unbalanced binary search tree, but 
// modifications have to observe and restore the height balance of the
// sub-trees.
// 	SEARCHING:
// 	Seaching for a specific key in AVL tree can be done the same way
// 	as that of any balanced or unbalanced binary search tree. In order for
// 	search to work effectively it has to employ a comparison function
// 	which establishes a total order (or at least a total preorder) on the 
// 	set of keys. The number of comparisons required for succesful search
// 	is very close to h, so both are in O(log n).
// 	
// 	TRAVERSAL:
// 	As a read-only operator the traversal of an AVL tree functions the same
// 	way as on any other binary tree. Exploring all n nodes of the tree
// 	visits each link exactly twice: one downward visit to enter the subtree
// 	rooted by that node, another visit upward to leave that node's subtree
// 	after having explored it.
//	
//	INSERT:
//	When inserting a node into an AVL tree, you initially follow the same
//	process as inserting into a Binary Search Tree. If the tree is empty,
//	then the node is inserted as the root of the tree. In case the tree
//	has not been empty then we go down the root, and recursively go down
//	the tree searching for the location to insert the new node. This
//	traversal is guided by the comparison function. In this case, the node
//	always replaces a NULL reference (left or right) of an external node
//	in the tree i.e., the node is either made a left-child or a 
//	right-child of the external node.
//	After this insertion if a tree becomes unbalanced, only ancestors of
//	the newly inserted node are unbalanced. This is because only those
//	nodes have their sub-trees altered. So it is necessary to check each
//	of the node's ancestors for consistency with the invariants of AVL
//	trees: this is called "retracing". This is achieved by considering the
//	balance factor of each node.
//	Since with a single insertion the height of an AVL subtree cannot 
//	increase by more than one, the temporary balance factor of a node
//	after an insertion will be in the range [-2,+2]. For each node checked,
//	if the temporary balance factor remains in the range [-1,+1] then only
//	an update of the balance factor and no rotation is necessary. However,
//	if the temporary balance factor becomes less than -1 or greater than 1,
//	the subtree rooted at this node is AVL unbalanced, and a rotation is
//	needed. With insertion as the code below shows, the adequate rotation
//	immediatly perfectly rebalances the tree.
//
//	
//

namespace ft
{
	template <class T1, class T2>
		struct node{
			pair<T1,T2> data;
			node* left;
			node* right;
			node* parent;
			int	bf;
		};
	template <class T1, class T2, class Alloc =
		std::allocator<node<T1,T2> > >
		struct tree{
			typedef node<T1,T2>	Node;
			typedef pair<T1,T2>	Data;
			typedef Alloc		allocator_type;

			tree(const allocator_type& alloc = allocator_type())
				:root(0), allocator(alloc){
					std::cout << "Hello, World!" << std::endl;
				}
			~tree(void){
				tree_free(root);
				std::cout << "Goodbye, World!" << std::endl;
			}
			// construct new node
			Node*	node_new(Data data, Node* Parent){
				Node* node = allocator.allocate(1);
				node->left = NULL;
				node->right = NULL;
				node->parent = Parent;
				node->data = data;
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
				if (*Root == NULL){
					*Root = node_new(data, NULL);
					return ;
				}
				if ((*Root)->left==NULL || (*Root)->right==NULL){
					if (data.first > (*Root)->data.first)
						(*Root)->right = node_new(data, *Root);
					else
						(*Root)->left = node_new(data, *Root);
					return ;
				}
				if (data.first > (*Root)->data.first)
					insert(&((*Root)->right), data);
				else
					insert(&((*Root)->left), data);
			}
			void	insert(Node** Root, Data data){
				insert_ext(Root,data);
				update_bf(*Root);
				// rebalance(*Root);
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
			// "rebalanced". The giben repair tools are the so-called "'tree rotations'"
			//
			void	rebalance(Node* Root){
				if (Root == NULL)
					return ;
				rebalance(Root->left);
				rebalance(Root->right);
				if (Root->bf == 2)
					rotate_left(Root, Root->right);
			}
			// rotate left bf +2
			Node*	rotate_left(Node* X, Node* Z){
				Node* papa = X->parent;
				Node* t23 = Z->left;
				X->right = t23;
				if (t23 != NULL)
					t23->parent = X;
				Z->left = X;
				X->parent = Z;
				Z->parent = papa;
				papa->right = Z;
				if (Z->bf == 0){
					X->bf = 1;
					Z->bf = -1;
				}else{
					X->bf = 0;
					Z->bf = 0;
				}
				return Z;
				// parent of X right node should be pointing to Z;
				// X should be replaced by Z in root node.
			}
			// have to take a closer look into this!
			// not sure if it's working as intended :3
			// rotate right bf -2
			Node*	rotate_right(Node* X, Node* Z)
			{
				Node* t23 = Z->left;
				X->left = t23;
				if (t23 != NULL)
					t23->parent = X;
				Z->right = X;
				X->parent = Z;
				if (Z->bf == 0){
					X->bf = 1;
					Z->bf = -1;
				}else{
					X->bf = 0;
					Z->bf = 0;
				}
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
					std::cout << node->data << node->bf << std::endl;

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
