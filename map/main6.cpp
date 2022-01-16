#include "map.hpp"
#include <iostream>

int     main()
{

    ft::map<int, int> mymap;
    ft::map<int, int> mymap2;
    
    // for (int i = 0; i < 20; i++){
    //     mymap.insert(ft::make_pair(i,i*i));
    // }
    // mymap2= mymap;
    // mymap2.debug();

    ft::map<int, int>::iterator it1;
    it1 = mymap.begin();

    for (;it1 != mymap.end(); ++it1){
        std::cout << "TEST" << std::endl;
    }

    return 0;
}