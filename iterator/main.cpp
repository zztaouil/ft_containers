#include "board.hpp"
#include <iostream>
#include "iterators.hpp"
#include <string>


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
}

/* int		main()
{
	int arr[] = {1, 2, 3, 4, 5};

	ft::iterator<int> it;
	it = arr;
	ft::iterator<int> ite;
	ite = arr + 5;

	while (it != ite){
		std::cout << it.get_ptr() << std::endl;
		it++;
	}
	return 0;
} */
