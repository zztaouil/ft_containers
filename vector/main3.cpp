#include "vector.hpp"
#include "iostream"

int main()
{
    ft::vector<std::string> ft_v(5, "string");

    ft_v.insert(ft_v.begin(), ft_v.begin(), ft_v.end());
    ft_v.debug();
    return 0;
}
