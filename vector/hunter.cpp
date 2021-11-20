#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

int	main()
{
	ft::vector<int> vec1(6,10);
	ft::vector<int> vec2(vec1.begin(), vec1.end());
	
	vec1.debug();
	vec2.debug();
}
