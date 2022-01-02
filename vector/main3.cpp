#include "vector.hpp"
#include "iostream"

int main()
{
    ft::vector<std::string> ft_v(20, "string");

    ft_v.insert(ft_v.begin()+10, 100, "hello");
    ft_v.debug();
    return 0;
}