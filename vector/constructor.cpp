#include "vector.hpp"
#include "../iterator/iterators.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <iomanip>

using namespace std;

int		main()
{
	ft::vector<int> vec1(10, 69);
	ft::vector<int> vec2(vec1.begin(), vec1.end());

	vec1.debug();

	vec2.debug();
	//for (size_t i=0; i<vec2.size(); i++) cout << vec2.at(i) << endl;
	return 0;
}
