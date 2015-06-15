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
    typedef typename boost::mpl::at<ScaleConversion, Scale>::type ScaleIntType;
    typedef typename boost::units::make_scaled_unit<
        BaseUnit,
        boost::units::scale<10,
                            boost::units::static_rational<
                                ScaleIntType::value - ScaleToOriginal>>>::type
        type;
};
template <class Scale, class BaseUnit, int ScaleToOriginal>
using GenUnit = typename GenUnit_impl<Scale, BaseUnit, ScaleToOriginal>::type;

#define MAKE(BASE_UNIT, BASE_UNIT_SUFFIX, SCALE_TO_ORIGINAL)             \
    boost::units::quantity<GenUnit<Scale_k, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##k##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_k, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_M, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##M##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_M, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_G, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##G##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_G, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_T, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##T##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_T, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
                                                                         \
    boost::units::quantity<GenUnit<Scale_, boost::units::si::BASE_UNIT,  \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##BASE_UNIT_SUFFIX(long double in)                       \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_, boost::units::si::BASE_UNIT,                 \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
                                                                         \
    boost::units::quantity<GenUnit<Scale_m, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##m##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_m, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_u, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##u##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_u, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_p, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##p##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_p, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }                                                                    \
    boost::units::quantity<GenUnit<Scale_f, boost::units::si::BASE_UNIT, \
                                   SCALE_TO_ORIGINAL>> inline            \
    operator"" _##f##BASE_UNIT_SUFFIX(long double in)                    \
    {                                                                    \
        return boost::units::quantity<                                   \
            GenUnit<Scale_f, boost::units::si::BASE_UNIT,                \
                    SCALE_TO_ORIGINAL>>::from_value(in);                 \
    }
MAKE(length, m, 0)
MAKE(mass, g, 3)
MAKE(time, s, 0)

#endif
