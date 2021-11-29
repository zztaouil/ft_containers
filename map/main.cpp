#include "tree.hpp"
#include <iostream>
#include <stdlib.h>
// namespace ft
//
int	main()
{
	ft::node<int,int>*	root = ft::new_node<int,int>(ft::make_pair<int,int>(1,69));
	std::cout << "root address: " << root << std::endl;
	std::cout << "root left addr: " << root->left << std::endl;
	std::cout << "root right addr: " << root->right << std::endl;

	ft::insert<int,int>(&root, ft::make_pair<int,int>(3, 98));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(2, 9));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(8, 8));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(42, 9));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(7, 96));
	std::cout << "After insertion" << std::endl;
	std::cout << "root address: " << root << std::endl;
	std::cout << "root left addr: " << root->left << std::endl;
	std::cout << "root right addr: " << root->right << std::endl;

	ft::inorder(root);

	ft::inorder_del(root);	
	return 0;
}
