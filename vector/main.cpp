#include "vector.hpp"

int		main()
{
	int t[] = {1, 2, 3, 4, 5};

	vector<int>	v(t, t+5);

	for (int i = 0; i < 5; i++){
		std::cout << v.at(i) << std::endl; 
	}

	return 0;
}