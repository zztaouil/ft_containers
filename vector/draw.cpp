#include <iostream>
#include <vector>
#include <iterator>

void	debug(std::vector<int> &vec)
{
	std::vector<int>::iterator it = vec.begin();
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
	debug(vec1);
	vec1.assign(7, 100);
	debug(vec1);
	vec2.assign(vec1.begin(), vec1.end());
	debug(vec2);

	return 0;
}
