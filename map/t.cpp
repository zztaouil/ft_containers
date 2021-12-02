#include "pair.hpp"
#include <iostream>

int	main()
{
	ft::pair<int,int> pp=ft::make_pair(42,69);
	std::cout << pp << std::endl;
	return 0;
}
