#include <map>
#include <iostream>
#include <utility>

int main()
{
    std::map<int, int> mymap1;
    std::map<int, int> mymap2;

    for (int i = 0; i<20; i++){
        mymap1.insert(std::make_pair(i, i+3));
    }
    mymap2 = mymap1;
    mymap1.clear();
    std::map<int, int>::iterator it1 = mymap1.begin();
    std::map<int, int>::const_iterator it2 = mymap1.begin();
    std::cout << mymap1.size() << " @ " << mymap2.size() << std::endl;
}