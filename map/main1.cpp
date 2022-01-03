#include "map.hpp"

int		main()
{
	ft::map<int,int>	mymap;

	for (int i=0; i<100; i++)
		mymap.insert(ft::make_pair(i, 69));
	mymap.debug();
	return 0;
}

