#include "map.hpp"

int main ()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator itlow,itup;

 mymap['a']=69;
 mymap['a']=69;
// mymap.insert(ft::make_pair('a', 66));
//  mymap['a']=69;
    mymap.debug();
//   std::cout << *mymap.begin() << std::endl;
//   mymap['b']=40;
//   mymap['c']=60;
//   mymap['d']=80;
//   mymap['e']=100;

//   itlow=mymap.lower_bound ('b');  // itlow points to b
// //   itup=mymap.upper_bound ('d');   // itup points to e (not d!)

//   mymap.erase(itlow,itup);        // erases [itlow,itup)

//   // print content:
//   for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//     std::cout << it->first << " => " << it->second << '\n';

  return 0;
}