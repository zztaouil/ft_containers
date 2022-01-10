#include "map.hpp"
#include <iostream>

int	main()
{
	ft::map<int, int> mymap;
	mymap.insert(ft::make_pair(4,4));
	mymap.debug();
	return 0;
}
