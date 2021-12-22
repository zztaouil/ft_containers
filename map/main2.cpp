#include "map.hpp"
#include <iostream>
#include <string>

int	main()
{
	ft::map<int, int> mymap;
	
	for (int i = 0; i < 100; i++){
		mymap.insert(ft::make_pair
				(i, 69)
				);
	}
	mymap.debug();
	std::cout << "map::size: " << mymap.size() << std::endl;
	ft::map<int, int>::iterator it = mymap.begin();
	ft::map<int, int>::reverse_iterator rit = mymap.rbegin();
	std::cout << *rit << std::endl;
	return 0;
}
