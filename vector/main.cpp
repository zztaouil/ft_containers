//#include "vector.hpp"
#include "iterators.hpp"
#include <vector>

using namespace std;
int 	main()
{
	int arr[] = {1, 2, 4, 5, 6};
	Iterator<int> it1;
	Iterator<int> it2;
	it1 = arr;
	it2 = arr+1;

	//cout << it << endl << endl;
	//cout <<(bool )(it1 == it2)  << endl << endl;

	vector<int> A;
	for (int i=0;i<50;i++)
		A.push_back(i);
	vector<int>::iterator it=A.begin();

	cout << it->(3) << endl;
	

	return 0;
}
