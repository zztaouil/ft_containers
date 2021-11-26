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

	std::cout << "Capacity : " << vec.capacity() << std::endl;
	std::cout << "Size : " << vec.size() << std::endl << std::endl;
}

int	main()
{
	std::vector<int> vec1(4,42);
	std::vector<int> vec2(6,42);
	
	vec1.resize(5);
	debug<int>(vec1);
	debug<int>(vec2);

	return 0;
}
