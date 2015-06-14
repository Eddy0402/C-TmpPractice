/*
 * Swap.cpp: A generic iterator swap function that choose implementation depends
 *           on data type
 */

#include <list>
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <vector>
#include "MetaFunctions.hpp"

// Swap
template <bool isfast>
struct swap_impl;

template <>
struct swap_impl<false> {
    template <class A, class B>
    static void doIt(A i1, B i2)
    {
        typename A::value_type tmp = *i1;
        *i1 = *i2;
        *i2 = tmp;
        std::cout << "Diff" << std::endl;
    };
};

template <>
struct swap_impl<true> {
    template <class A, class B>
    static void doIt(A i1, B i2)
    {
        std::swap(*i1, *i2);
        std::cout << "Same" << std::endl;
    };
};

template <class A, class B>
void Swap(A i1, B i2)
{
    if_<std::is_same<typename A::value_type, typename B::value_type>::value,
        swap_impl<true>, swap_impl<false>>::doIt(i1, i2);
}

void SwapTest()
{
    std::vector<float> a{1, 3, 4, 6, 4};
    std::list<int> b{1, 3, 4, 6, 4};
    Swap(a.begin() + 1, b.begin());
    Swap(b.begin(), b.begin());
    for (auto item : a) {
        std::cout << item << std::endl;
    }
}
