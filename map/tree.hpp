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
		};
	template <class T1, class T2>
		node<T1,T2>*	new_node(pair<T1,T2> Data){
			node<T1,T2>* node = new ft::node<T1,T2>;
			node->data = Data;
			node->left = NULL;
			node->right = NULL;
			return node;
		}
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
 			return search(root->right, key);
		}
// A new key is always inserted at the leaf. We start searching a key from
// the root until we hit a leaf node. Once a leaf node is found, the new 
// node is added as a chilf of the leaf node
	template <class T1, class T2>
		void		insert(node<T1,T2>** root, pair<T1,T2> data){
// if subtree is empty
			if (*root == NULL){
				*root = new_node(data);
				return ;
			}
			if (data.first > (*root)->data.first)
				insert(&((*root)->right), data);
			else	
				insert(&((*root)->left), data);
		}
	template <class T1, class T2>
		void		inorder(node<T1,T2>* root){
			if (root == NULL)
				return ;
			inorder(root->left);
			std::cout << root->data.first << " " << root->data.second << std::endl;
			inorder(root->right);
		}
	template <class T1, class T2>
		void		inorder_del(node<T1,T2>* root){
			if (root == NULL)
				return ;
			inorder_del(root->left);
			if (root != NULL)	
				delete root;
			inorder_del(root->right);
		}
}
#endif
