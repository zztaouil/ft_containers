#include <map>
#include "map.hpp"
#include <iostream>
#include <ctime>


// int		main()
// {	
// 	ft::map<int, int> mymap;
// 	time_t	timer;
// 	double seconds;

// 	timer = time(NULL);
// 	for (int i = 0; i < 1e2; i++){
// 		mymap.insert(ft::make_pair(i, i+2));
// 		std::cout << i << std::endl;
// 	}
// 	seconds = difftime(time(NULL), timer);
// 	std::cout << "Execution time: " << seconds << std::endl;
// 	mymap.debug();
// 	return 0;
// }

int	main()
{
            ft::map<int, int> m;

            for (size_t i = 0; i < 50; i++){
                m.insert(ft::make_pair(i, i));
            }
            ft::map<int, int>::iterator it = m.begin();

            for (;it!=m.end();it++)
                std::cout << *it << std::endl;
            
            return 0;
}