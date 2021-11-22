#include "vector.hpp"
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
	vec3.debug();


	vec2.swap(vec1);

	vec2.debug();

	return 0;
}
