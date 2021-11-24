#include "vector.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

using namespace std;
// constructors
void	constructors(void)
{	
	std::cout << std::setw(40) << "CONSTRUCTORS" << std::endl;
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
void	operatorassign(void)
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
void	max_size(void)
{		std::cout << std::setw(40) << "MAX SIZE" << std::endl;

	ft::vector<int> foo(20, 69);
	std::cout << "size: " << foo.size() << std::endl;
	std::cout << "capacity: " << foo.capacity() << std::endl;
	std::cout << "max_size: " << foo.max_size() << std::endl;
}

// Assign
void	assign(void)
{
	std::cout << std::setw(40) << "ASSIGN" << std::endl;
	ft::vector<char>	bar(20, 'a');	
	ft::vector<char>	foo(20, 'z');
	foo.debug();
	foo.assign(bar.begin(), bar.end());
	foo.debug();
	bar.assign(90, 'z');
	bar.debug();
}
// resize
void	resize(void)
{
	std::cout << std::setw(40) << "RESIZE" << std::endl;
	ft::vector<int> foo(25,42);
	foo.resize(40);

}
// At
void	at(void)
{
	std::cout << std::setw(40) << "AT" << std::endl;
	ft::vector<int> bar(69, 69);
	bar.at(68);
}
// insert
void	insert(void)
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
void	erase(void)
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
void	swap(void)
{
	std::cout << std::setw(40) << "SWAP" << std::endl;
	ft::vector<int> bar(42,42);
	ft::vector<int> foo(69,69);

	// bar.swap(foo);
	bar.debug();
	foo.debug();

}
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
int		main()
{
	constructors();
	operatorassign();
	max_size();
	assign();
	resize();
	at();
	insert();
	erase();
	swap();
	foo();
	bar();
	return 0;
}
