#ifndef _UNIT_H
#define _UNIT_H

#include <boost/units/base_unit.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/io.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <iostream>

class Scale_k;
class Scale_M;
class Scale_G;
class Scale_T;
class Scale_;
class Scale_m;
class Scale_u;
class Scale_p;
class Scale_f;

typedef boost::mpl::map<boost::mpl::pair<Scale_k, boost::mpl::int_<3>>,
                        boost::mpl::pair<Scale_M, boost::mpl::int_<6>>,
                        boost::mpl::pair<Scale_G, boost::mpl::int_<9>>,
                        boost::mpl::pair<Scale_T, boost::mpl::int_<12>>,
                        boost::mpl::pair<Scale_, boost::mpl::int_<0>>,
                        boost::mpl::pair<Scale_m, boost::mpl::int_<-3>>,
                        boost::mpl::pair<Scale_u, boost::mpl::int_<-6>>,
                        boost::mpl::pair<Scale_p, boost::mpl::int_<-9>>,
                        boost::mpl::pair<Scale_f, boost::mpl::int_<-12>>>
    ScaleConversion;

template <class Scale, class BaseUnit, int ScaleToOriginal>
struct GenUnit_impl {
    using ScaleIntType = typename boost::mpl::at<ScaleConversion, Scale>::type;
    using type = typename boost::units::make_scaled_unit<
        BaseUnit,
        boost::units::scale<10,
                            boost::units::static_rational<
                                ScaleIntType::value - ScaleToOriginal>>>::type;
};
template <class Scale, class BaseUnit, int ScaleToOriginal>
using GenUnit = typename GenUnit_impl<Scale, BaseUnit, ScaleToOriginal>::type;

#define MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, SCALE, SCALE_TO_ORIGINAL)        \
    boost::units::quantity<GenUnit<Scale_##SCALE, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline                  \
    operator"" _##SCALE##BASE_UNIT_SUFFIX(long double in)                      \
    {                                                                          \
        return boost::units::quantity<                                         \
            GenUnit<Scale_##SCALE, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                       \
    }

#define MAKE(BASE_UNIT, BASE_UNIT_SUFFIX, SCALE_TO_ORIGINAL)    \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, k, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, M, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, G, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, T, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, , SCALE_TO_ORIGINAL)  \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, m, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, u, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, p, SCALE_TO_ORIGINAL) \
    MAKE_ONE(BASE_UNIT, BASE_UNIT_SUFFIX, f, SCALE_TO_ORIGINAL)

MAKE(length, m, 0)
MAKE(mass, g, 3)
MAKE(time, s, 0)

inline void UnitTest()
{
    auto m = 1.0_kg;
    auto t = 32.0_ms;
    auto l = 12.0_km;
    std::cout << m << std::endl;
    std::cout << t << std::endl;
    std::cout << l << std::endl;
    std::cout << m* l* l / t / t << std::endl;
    std::cout << 1.0_kg * 1.0_mm * 1.0_km / 1.0_ms / 1.0_ms << std::endl;
}

#endif
