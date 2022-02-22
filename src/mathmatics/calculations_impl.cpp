#include "calculations_impl.hpp"

namespace mathmatics
{

float calculations_impl::map(
    float in,
    float min_in_range,
    float max_in_range,
    int min_out_range,
    int max_out_range) const
{
    return min_out_range +
        (in - min_in_range) *
        (max_out_range - min_out_range) /
        (max_in_range - min_in_range);
}

short calculations_impl::constrict(
    const short value, const short minimum, const short maximum) const
{
    return constrict<short>(value, minimum, maximum);
}

int calculations_impl::constrict(
    const int value, const int minimum, const int maximum) const
{
    return constrict<int>(value, minimum, maximum);
}

double calculations_impl::constrict(
    const double value, const double minimum, const double maximum) const
{
    return constrict<double>(value, minimum, maximum);
}

}
