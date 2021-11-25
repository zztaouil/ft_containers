#include <iostream>
#include <string>
#include "../vector/vector.hpp"
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
	ft::vector<int> vec1(6,42);
	ft::vector<int>::reverse_iterator rev_it1 = vec1.rbegin();
	ft::vector<int>::const_reverse_iterator rev_it2;

	rev_it2 = rev_it1;

	std::cout << *rev_it2 << std::endl;
	std::cout << *rev_it1 << std::endl;
	return 0;
}
