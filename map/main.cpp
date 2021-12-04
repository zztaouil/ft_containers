#include "tree.hpp"
#include <iostream>
#include <stdlib.h>
// namespace ft
// heap use after free. visiting a node two times
int	main()
{
	ft::node<int,int>*	root = ft::new_node<int,int>(ft::make_pair<int,int>(1,69));

	ft::insert<int,int>(&root, ft::make_pair<int,int>(3, 98));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(2, 9));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(8, 8));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(42, 9));
	ft::insert<int,int>(&root, ft::make_pair<int,int>(7, 96));

	std::cout << "pre order tree traversal" << std::endl;
	ft::preorder(root);
	std::cout << "in order tree traversal" << std::endl;
	ft::inorder(root);
	std::cout << "post order tree traversal" << std::endl;
	ft::postorder(root);

	std::cout << "maximum node: " << ft::tree_max(root)->data << std::endl;
	

	std::cout << "minimum node: " << ft::tree_min(root)->data << std::endl;
	
	std::cout << "tree height: " << ft::tree_height(root) << std::endl;

	ft::postorder_free(root);
	return 0;
}
