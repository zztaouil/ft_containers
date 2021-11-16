#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

template< class T>
struct iterator_traits<const T*>{};

#endif