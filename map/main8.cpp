#include "map.hpp"
#include <map>
#include <iostream>

template <typename Iter1, typename Iter2>
bool comparemaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }
struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};
bool   testmapConstructors()
{
    bool cond = true;
    std::map<char, int> first;
    ft::map<char, int> m_first;

    for (size_t i = 97; i < 110; i++)
    {
        first[i - 97] = i;
        m_first[i - 97] = i;
    }

    // std::map<char, int> copy(first);
    // ft::map<char, int> m_copy(m_first);

    // cond = first.size() == m_first.size() && comparemaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    // std::map<char, int> second(first.begin(), first.end());
    // ft::map<char, int> m_second(m_first.begin(), m_first.end());

    // cond = cond && second.size() == m_second.size() && comparemaps(second.begin(), second.end(), m_second.begin(), m_second.end());
    // std::map<char, int> third(second);
    // ft::map<char, int> m_third(m_second);

    // cond = cond && third.size() == m_third.size() && comparemaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    // std::map<char, int, classcomp> fourth;  // class as Compare
    // ft::map<char, int, classcomp> m_fourth; // class as Compare

    // cond = fourth.size() == m_fourth.size() && cond && comparemaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    // bool (*fn_pt)(char, char) = fncomp;
    // std::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    // ft::map<char, int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    // cond = fifth.size() == m_fifth.size() && cond && comparemaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    std::cout << first.size() << " " << m_first.size() << std::endl;
    
    first = std::map<char, int>();
    m_first = ft::map<char, int>();


    // cond = copy.size() == m_copy.size() && cond && comparemaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    std::cout << "before return" << std::endl;
    return cond;
}

int     main()
{
    std::cout << testmapConstructors() << std::endl;


    return 0;
}
