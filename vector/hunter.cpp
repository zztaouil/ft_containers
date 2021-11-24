#include "vector.hpp"
#include <string>
#include <iomanip>

int	foo()
{
	ft::vector<int> vec1;
	ft::vector<int> vec2(42,42);
	for (size_t i = 1; i <= 10; i++) vec1.push_back(i * 3);
	ft::vector<int> vec3;
	vec3 = vec2;

	vec1.debug();
	vec2.debug();
	vec3.debug();
	std::cout << "vec2 == vec3: " << (vec2 == vec3) << std::endl;
	std::cout << "vec1 == vec3: " << (vec1 == vec3) << std::endl;
	std::cout << "vec1 < vec2: " << (vec1 < vec2) << std::endl;
	std::cout << "vec1 > vec2: " << (vec1 > vec2) << std::endl;
	std::cout << "vec1 <= vec2: " << (vec1 <= vec2) << std::endl;
	std::cout << "vec2 <= vec3: " << (vec2 <= vec3) << std::endl;

	return 0;
}

int	bar()
{	
	int arr[] = {1, 2, 3, 4, 5, 6};
	ft::vector<int> vec1(arr, arr + sizeof(arr)/sizeof(int));
	
	ft::vector<int>::reverse_iterator rev_it = vec1.rbegin();
	ft::vector<int>::reverse_iterator rev_ite = vec1.rend();

	while (rev_it!=rev_ite){
		std::cout << *rev_it << std::endl;
		++rev_it;
	}
	vec1.debug();
	return 0;
}

int	main()
{	
	int arr[] = {1, 2, 3, 4, 5, 6};
	ft::vector<int> vec1(arr, arr + sizeof(arr)/sizeof(int));
	for (ft::vector<int>::const_reverse_iterator it = vec1.rbegin(); it != vec1.rend(); it++){
		std::cout << *it << std::endl;
	}
	return 0;
}
