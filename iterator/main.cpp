#include "board.hpp"
#include <iostream>
#include "iterators.hpp"
#include <string>

/*
int	main(void)
{
	int arr[] = {1, 2, 3, 4, 5};
	Iterator<int> it;
	it = arr;
	Iterator<int> ite;
	ite = arr + 5;
	ite-=1;
	std::cout << ite - it << std::endl;
	std::cout << "COMPAIRISON" << std::endl;
	std::cout << "it < ite " << (it < ite) << std::endl;
	std::cout << "it > ite " << (it > ite) << std::endl;
	std::cout << "offset derefence operator" << std::endl;
	std::cout << "it[2]: " << it[2] << std::endl;
	while (it != ite){
		std::cout << *it << std::endl;
		it++;
	}


	return 0;
}*/

int		main()
{
	int arr[] = {1, 2, 3, 4, 5};

	ft::random_access_iterator<int> it;
	ft::reverse_iterator<random_access_iterator<int>> rit(it);

	return 0;
}
