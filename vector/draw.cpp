#include <iostream>
#include <vector>
#include <iterator>

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
	std::cout << "Size : " << vec.size() << std::endl;
}
int	main()
{
	std::vector<int> vec1(10, 67);
	vec1.push_back(88);
	debug<int>(vec1);
	std::vector<int>::iterator it = vec1.insert(vec1.end(), 9, 42);
	debug<int>(vec1);


	return 0;
}
/*
					if (n > _capacity)
						reserve(_capacity * 2 + (n - _capacity));
					else
						reserve(_capacity * 2);
*/
