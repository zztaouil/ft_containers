#include <iostream>
#include <vector>
#include <iterator>

template <class T>
void	debug(std::vector<T> &vec)
{
	typename std::vector<T>::iterator it = vec.begin();
	for (;it != vec.end(); it++){
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}
int	main()
{
	std::vector<int> vec1;
	std::vector<char> vec2;
	vec1.assign(5,100);
	debug<int>(vec1);
	vec1.assign(7, 100);
	debug<int>(vec1);
	vec2.assign(vec1.begin(), vec1.end());
	debug<char>(vec2);

	return 0;
}
