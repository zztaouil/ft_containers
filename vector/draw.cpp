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
	std::cout << "Size : " << vec.size() << std::endl << std::endl;
}

int	main()
{
	std::vector<int> vec1(4,67);
	std::vector<int> vec2(6,42);
	vec1.push_back(88);
	vec2.insert(vec2.begin()+1, vec1.begin(), vec1.end());
	debug<int>(vec1);
	debug<int>(vec2);


	return 0;
}
/*
					if (n > _capacity)
						reserve(_capacity * 2 + (n - _capacity));
					else
						reserve(_capacity * 2);
*/
