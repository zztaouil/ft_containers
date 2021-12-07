#include "AVL.hpp"

int		main()
{
	ft::tree<char,char> t1;


	t1.insert(&t1.root, ft::make_pair('J', 'a'));
	t1.insert(&t1.root, ft::make_pair('F', 'b'));
	t1.insert(&t1.root, ft::make_pair('P', 'c'));
	t1.insert(&t1.root, ft::make_pair('D', 'd'));
	t1.insert(&t1.root, ft::make_pair('G', 'e'));
	t1.insert(&t1.root, ft::make_pair('L', 'e'));
	t1.insert(&t1.root, ft::make_pair('V', 'x'));
	t1.insert(&t1.root, ft::make_pair('C', 'g'));
	t1.insert(&t1.root, ft::make_pair('N', 'g'));
	t1.insert(&t1.root, ft::make_pair('S', 'g'));
	t1.insert(&t1.root, ft::make_pair('X', 'g'));
	t1.insert(&t1.root, ft::make_pair('Q', 'g'));
	t1.insert(&t1.root, ft::make_pair('U', 'g'));
	t1.insert(&t1.root, ft::make_pair('I', 'o'));
	t1.insert(&t1.root, ft::make_pair('Z','o'));
	t1.insert(&t1.root, ft::make_pair('A','o'));
	

	t1.tree_debug(t1.root);
	t1.tree_delete(&t1.root, t1.tree_search(t1.root, ft::make_pair('J','a')));
	t1.tree_delete(&t1.root, t1.tree_search(t1.root, ft::make_pair('F','b')));
	t1.tree_debug(t1.root);

//	t1.tree_inorder(t1.root);
//	std::cout << "tree max: " << t1.tree_max(t1.root)->data << std::endl;
//	std::cout << "tree min: " << t1.tree_min(t1.root)->data << std::endl;
//	std::cout << "tree height: " << t1.tree_height(t1.root) << std::endl;	
	return 0;
}

/*
 *
 * └──(65,a)
    ├──(8,b)
    │   ├──(5,d)
    └──(99,c)
        ├──(90,e)
        │   └──(95,e)
 * */
