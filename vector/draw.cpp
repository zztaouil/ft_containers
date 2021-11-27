#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"
template <class T>
void	debug(std::vector<T> &vec)
{
	typename std::vector<T>::iterator it = vec.begin();
	std::cout << "Elements are :\n";
	for (;it != vec.end(); it++){
		std::cout << *it << ' ';
	}
	std::cout << std::endl;

	std::cout << "Size : " << vec.size() << std::endl;
	std::cout << "Capacity : " << vec.capacity() << "\n\n";
}

//int	main()
//{
//	int arr[] = {1, 1, 2, 3, 5, 8, 13, 21};
//	std::vector<int> vec1(arr, arr + sizeof(arr) / sizeof(int));
//	std::vector<int> vec2(6,42);
//	debug<int>(vec1);
//	std::vector<int>::iterator it = vec1.erase(vec1.end()-4, vec1.end());
//	debug<int>(vec1);
//	std::cout << (it == vec1.end()) << std::endl;
//	debug<int>(vec2);
//
//	return 0;
//}

int	main()
{
	int arr[] = {1, 9, 2, 3, 5, 8, 13, 21};
	ft::vector<int> my_vec(arr, arr + sizeof(arr) / sizeof(int));
	std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
	
	debug<int>(vec);
	my_vec.debug();
	std::vector<int>::iterator it = vec.erase(vec.begin(), vec.end()-2);
	ft::vector<int>::iterator my_it = my_vec.erase(my_vec.begin(), my_vec.end()-2);
	debug<int>(vec);
	my_vec.debug();
	std::cout << (it == vec.end()) << std::endl;
	std::cout << (my_it == my_vec.end()) << std::endl;
	return 0;
}
