#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>

using namespace std;
int 	main()
{
	{	
		std::cout << "CONSTRUCTORS" << std::endl;
		ft::vector<int> first;
		ft::vector<int> second(4,100);
		ft::vector<int> third (second.begin(), second.end());
		ft::vector<int> fourth (third);

		int myints[] = {16, 2, 77, 29};
		ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

		std::cout << "The contents of fifth are:";
		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	
	{
		std::cout << "OPERATOR=" << std::endl;
		ft::vector<int> foo(3,0);
		ft::vector<int> bar(5,0);

		bar = foo;
		foo = ft::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << std::endl;
		std::cout << "Size of bar: " << int(bar.size()) << std::endl;

	}
	
	{
		std::cout << "MAX SIZE" << std::endl;

		ft::vector<int> foo(20, 69);
		std::cout << "size: " << foo.size() << std::endl;
		std::cout << "capacity: " << foo.capacity() << std::endl;
		std::cout << "max_size: " << foo.max_size() << std::endl;
	}

}
