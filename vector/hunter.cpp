#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

int	main()
{
	ft::vector<int> vec1;

	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);

	//ft::vector<int> vec2(vec1.begin(), vec1.end());
	std::cout << vec1.capacity() << std::endl;
	vec1.debug();
}
