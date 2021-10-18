#include "vector.hpp"

/* int		main()
{
	char t[] = {'t', 'e', 's', 't', '!'};

	vector<char>	v(t, t+5);


	v.push_back(42);
	v.push_back(43);
	v.push_back(43);
	v.push_back(43);
	v.push_back(43);
	v.push_back(43);
	v.push_back(43);





	v.debug();

	return 0;
} */

int		main()
{
	vector<int> v(5, 42);

	v.debug();

	v.reserve(10);

	v.debug();

	return 0;
}

/*

if n < _size
	shrink to [0, n]

if n > _capacity
	realloc and fill

if n > _size and n < _capacity
	enlarge to [0, n]
	val to the rest 



*/