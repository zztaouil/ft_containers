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
	for (size_t i = 1; i <= 10; i++) vec1.push_back(i * 3);
	ft::vector<int> vec3;
	vec3 = vec2;

	vec1.debug();
	vec2.debug();

	std::cout << (vec2 <= vec3) << std::endl;

	swap(vec1, vec2);
	vec1.debug();
	vec2.debug();


	return 0;
}
