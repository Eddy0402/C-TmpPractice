#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <typeinfo>
#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>

#include "MetaFunctions.hpp"
void SwapTest();

#include "Unit.hpp"

using namespace boost::mpl;

int main()
{
    auto m = 1.0_kg;
    std::cout << m << std::endl;
    auto l = 1.0_km;
    std::cout << l << std::endl;
    auto t = 1.0_ks;
    std::cout << t << std::endl;
    std::cout << m * l * l/ t / t << std::endl;
    std::cout << 1.0_kg * 1.0_mm * 1.0_km / 1.0_ms / 1.0_ms << std::endl;
//    std::cout << 1.0_kg + 1.0_mm << std::endl;
}
