#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

using namespace std;
int 	main()
{
	// constructors
	{		std::cout << std::setw(40) << "CONSTRUCTORS" << std::endl;
		ft::vector<int> first;
		ft::vector<int> second(4,100);
		ft::vector<int> third (second.begin(), second.end());
		ft::vector<int> fourth (third);
		int myints[] = {16, 2, 77, 29, 69, 69, 32, 124, 412};
		ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
		std::cout << "The contents of fifth are:";
		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << "\n";
	}
	// operator =
	{
		std::cout << std::setw(40) << "OPERATOR=" << std::endl;
		ft::vector<int> foo(3,0);
		ft::vector<int> bar(5,0);

		bar = foo;
		foo = ft::vector<int>();

		std::cout << "Size of foo: " << int(foo.size()) << std::endl;
		std::cout << "Size of bar: " << int(bar.size()) << std::endl;
	}

	// max size	
	{		std::cout << std::setw(40) << "MAX SIZE" << std::endl;

		ft::vector<int> foo(20, 69);
		std::cout << "size: " << foo.size() << std::endl;
		std::cout << "capacity: " << foo.capacity() << std::endl;
		std::cout << "max_size: " << foo.max_size() << std::endl;
	}

	// Assign
	{		std::cout << std::setw(40) << "ASSIGN" << std::endl;
		ft::vector<char>	bar(20, 'a');	
		ft::vector<char>	foo(20, 'z');
		foo.debug();
		foo.assign(bar.begin(), bar.end());
		foo.debug();
		bar.assign(90, 'z');
		bar.debug();
	}
	// resize
	{
		std::cout << std::setw(40) << "RESIZE" << std::endl;
		ft::vector<int> foo(25,42);
		foo.resize(40);

	}
	// At
	{
			std::cout << std::setw(40) << "AT" << std::endl;
		ft::vector<int> bar(69, 69);
		bar.at(68);
	}
	// insert
	{
		std::cout << std::setw(40) << "INSERT" << std::endl;
		ft::vector<int> foo(10);
		ft::vector<int> bar(7, 48);
		for (int i = 0; i < 10; i++) foo[i] = 2 * i;
		foo.debug();
		foo.insert(foo.begin() + 5, 11, 80);
		foo.debug();
		bar.debug();
		bar.insert(bar.begin() + 3,foo.begin(), foo.end());
		bar.debug();
	}
	//  erase
	{
		std::cout << std::setw(40) << "ERASE" << std::endl;
		ft::vector<int> foo;
		for (int i = 0; i < 10; i++) foo.push_back(2 * (i+1));
		foo.debug();
		foo.erase(foo.begin() + 2);
		foo.debug();
		foo.erase(foo.begin()+2, foo.begin()+6);
		foo.debug();

	}
	// swap
	{
		std::cout << std::setw(40) << "SWAP" << std::endl;
		ft::vector<int> bar(42,42);
		ft::vector<int> foo(69,69);

		// bar.swap(foo);
		bar.debug();
		foo.debug();

	}
}
