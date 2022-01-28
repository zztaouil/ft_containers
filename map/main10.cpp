#include <iostream>
#include "map.hpp"

int	main()
{
	ft::map<int, int> mymap;

	for(int i = 0; i<10; i++)
		mymap.insert(ft::make_pair(i,i));

	mymap.debug();

	mymap.lower_bound(4);
	return 0;
}
