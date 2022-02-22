#ifndef MATHMATICS_CALCULATIONS_IMPL_HPP
#define MATHMATICS_CALCULATIONS_IMPL_HPP

#include "calculations.hpp"

namespace mathmatics
{

class calculations_impl : public calculations
{
public:
    float map(
        float in,
        float min_in_range,
        float max_in_range,
        int min_out_range,
        int max_out_range) const override;

    short constrict(short value, short minimum, short maximum) const override;

    int constrict(int value, int minimum, int maximum) const override;

    double constrict(
        double value, double minimum, double maximum) const override;

private:
    template<typename T>
    T constrict(T value, T minimum, T maximum) const
    {
        return (value < minimum) ? minimum : ((value > maximum) ? maximum : value);
    }
};

}

#endif
