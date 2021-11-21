#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

int	main()
{
	ft::vector<int> vec1;
	ft::vector<int> vec2(42,42);

	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);
	vec1.push_back(24);

	vec1.debug();
	vec1.swap(vec2);
	vec1.debug();
	vec2.debug();

}
