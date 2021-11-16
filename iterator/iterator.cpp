#include "iterator.hpp"
#include <iostream>

class random_iterator{
	

};

int	main()
{
	iterator<random_iterator, int> it;
	std::cout << "sizeof: " << sizeof(iterator<random_iterator, int>::value_type) << std::endl;
	return 0;
}
