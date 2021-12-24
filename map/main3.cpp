#include <iostream>
#include <map>
#include <utility>
#include <functional>

int	main()
{
	std::map<int, int, std::greater<int> > mymap;

	for (int i=0; i<10; i++)
		mymap.insert(std::make_pair(i, 69));

	std::cout << (--mymap.end())->first << std::endl;
	return 0;
}
