//#include "vector.hpp"
#include "iterators.hpp"
#include <vector>
#include <string>
#include <iterator>

using namespace std;
int 	main()
{
	int arr[] = {1, 2, 4, 5, 6};
	Iterator<int> it1;
	Iterator<int> it2;
	Iterator<string> it3;
	it1 = arr;
	it2 = arr+1;

	cout << it1;
	cout << ++it1;
	cout <<(bool )(it1 == it2) << endl;



	return 0;
}
