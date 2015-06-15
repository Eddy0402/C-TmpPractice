#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <typeinfo>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/begin.hpp>

#include "MetaFunctions.hpp"
void SwapTest();

#include "Unit.hpp"

namespace mpl = boost::mpl;

using before = boost::mpl::vector<int, float>;
using after =
    boost::mpl::insert<before, boost::mpl::begin<before>::type, double>::type;

int main()
{
    static_assert(boost::mpl::equal<mpl::vector<double, int, float>, after>::type::value, "Not equal");

    auto m = 1.0_kg;
    std::cout << m << std::endl;
    auto l = 1.0_km;
    std::cout << l << std::endl;
    auto t = 1.0_ms;
    std::cout << t << std::endl;
    std::cout << m* l* l / t / t << std::endl;
    std::cout << 1.0_kg * 1.0_mm * 1.0_km / 1.0_ms / 1.0_ms << std::endl;
    //    std::cout << 1.0_kg + 1.0_mm << std::endl;
}
