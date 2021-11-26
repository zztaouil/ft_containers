#include <iostream>
#include <string>
#include <vector>
#include <iterator>
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
	int arr[] = {1, 1, 2, 3, 5, 8, 13};
	std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(int));
	ft::vector<int> my_vec(arr, arr + sizeof(arr)/sizeof(int));
	std::vector<int>::reverse_iterator rev_it1 = vec.rbegin();
	ft::vector<int>::reverse_iterator my_rev_it1 = my_vec.rbegin();
//	std::vector<int>::reverse_iterator rev_it2 = vec.rend();
//	ft::vector<int>::reverse_iterator my_rev_it2 = my_vec.rend();


	std::cout << *rev_it1++ << std::endl;
	std::cout << *my_rev_it1++ << std::endl;

	std::cout << *rev_it1 << std::endl;
	std::cout << *my_rev_it1 << std::endl;
	return 0;
}
