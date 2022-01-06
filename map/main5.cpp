#include "map.hpp"
#include <iostream>

int main ()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;
  mymap.debug();
  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  std::cout << itlow->first << "==>" << itlow->second << std::endl;
  std::cout << itup->first << "==>" << itup->second << std::endl;
  return 0;
}
