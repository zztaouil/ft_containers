#include "pair.hpp"
#include <iostream>

int	main()
{
	ft::pair<int, int> pp(42, 69);
	ft::pair<int, int> op(pp);
	

	std::cout << op.first << " " << op.second << std::endl;
	std::cout << pp.first << " " << pp.second << std::endl;
	return 0;
}
