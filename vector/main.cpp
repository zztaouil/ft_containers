#include "vector.hpp"

int		main()
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
}