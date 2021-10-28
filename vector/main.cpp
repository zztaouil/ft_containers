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
	it1 = arr;
	it2 = arr+1;

	cout << it1 << endl;
	cout <<(bool )(it1 == it2)  << endl << endl;
	
	vector<string> A;
	string str = "test123";
	A.push_back(str);
	vector<string>::iterator it4 = A.begin();
	cout << it4->length() << endl;
	return 0;
}
