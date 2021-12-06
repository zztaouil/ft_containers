#ifndef TREE_HPP
# define TREE_HPP

# include "pair.hpp"
# include <iostream>

// we call tree balanced if for all nodes the difference between the heights
// of left and right subtrees is not greater than 1.
namespace ft
{

	template <class T1, class T2>
		struct node{
			pair<T1,T2> data;
			node* left;
			node* right;
			node* parent;
		};
	template <class T1, class T2>
		node<T1,T2>*	new_node(pair<T1,T2> Data, node<T1,T2>* Parent){
			node<T1,T2>* node = new ft::node<T1,T2>;
			node->data = Data;
			node->left = NULL;
			node->right = NULL;
			node->parent = Parent;
			return node;
		}
// SEARCHING
	template <class T1, class T2>
		node<T1,T2>*	search(node<T1,T2>* root, T1 key){
// subtree with root root null
 			if (root == NULL)
 				return NULL;
// key equals root->key
			if (root->data.first == key)
				return root;
// key is smaller than root's key
// then we know that we should go search the left child
			if (key < root->data.first)
				return search(root->left, key);
// else key is larger than the root's key
// search the right child of root
			else	
				return search(root->right, key);
		}

// INSERTION
// A new key is always inserted at the leaf. We start searching a key from
// the root until we hit a leaf node. Once a leaf node is found, the new 
// node is added as a chilf of the leaf node
	template <class T1, class T2>
		void		insert(node<T1,T2>** root, pair<T1,T2> data){
// if subtree is empty
			if (*root == NULL){
				*root = new_node(data, *root);
				return ;
			}
			if (data.first > (*root)->data.first)
				insert(&((*root)->right), data);
			else	
				insert(&((*root)->left), data);
		}

// DEPTH FIRST TRAVERSAL	
	template <class T1, class T2>
		void		inorder(node<T1,T2>* root){
			if (root == NULL)
				return ;
			inorder(root->left);
			std::cout << root->data.first << " " <<
				root->data.second << std::endl;
			inorder(root->right);
		}
	template <class T1, class T2>
		void		preorder(node<T1,T2>* root){
			if (root == NULL)
				return ;
			std::cout << root->data.first << " " <<
				root->data.second << std::endl;
			preorder(root->left);
			preorder(root->right);
		}
	template <class T1, class T2>
		void		postorder(node<T1,T2>* root){
			if (root == NULL)
				return ;
			postorder(root->left);
			postorder(root->right);
			std::cout << root->data.first << " " <<
				root->data.second << std::endl;
		}
	// del
	template <class T1, class T2>
		void		postorder_free(node<T1,T2>* root){
			if (root == NULL)
				return ;
			postorder_free(root->left);
			postorder_free(root->right);
			delete root;
		}
// MAXIMUM AND MINIMUM 
	template <class T1, class T2>
		node<T1,T2>*	tree_max(node<T1,T2>* root){
			while (root->right != NULL)
				root=root->right;
			return root;
		}
	template<class T1, class T2>
		node<T1,T2>*	tree_min(node<T1,T2>* root){
			while (root->left != NULL)
				root = root->left;
			return root;
		}
// Succesor and predecessor
// Node Parent
		
// the successor of a node x is the node with the smallest key greater than
// x's key.
	template <class T1, class T2>
		node<T1,T2>*	tree_successor(node<T1,T2>* x){
			if (x->right != NULL)
				return tree_min(x->right);
			node<T1,T2>*	y=x->parent;
			while (y!=NULL && x == y->right){
				x = y;
				y = y->parent;
			}
			return y;
		}
	template <class T1, class T2>
		node<T1,T2>*	tree_predecessor(node<T1,T2>* x){
			if (x->left != NULL)
				return tree_max(x->left);
			node<T1,T2>* y=x->parent;
			while (y!=NULL && x == y->left){
				x = y;
				y = y->parent;
			}
			return y;
		}
	template <class T1, class T2>
		size_t	tree_height(node<T1,T2>* root){
			if (root == NULL)
				return -1;
			size_t left_height = tree_height(root->left);
			size_t right_height = tree_height(root->right);
			if (left_height > right_height)
				return left_height+1;
			else
				return right_height+1;
		}
}
#endif
