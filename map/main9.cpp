#include <map>
#include "map.hpp"
#include <iostream>
#include <ctime>


int		main()
{	
	ft::map<int, int> mymap;
	time_t	timer;
	double seconds;

	timer = time(NULL);
	for (int i = 0; i < 1e6; i++){
		mymap.insert(ft::make_pair(i, i+2));
		std::cout << i << std::endl;
	}
	seconds = difftime(time(NULL), timer);
	std::cout << "Execution time: " << seconds << std::endl;
	// mymap.debug();
	return 0;
}

