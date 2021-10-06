#include "calculations.hpp"

namespace mathmatics
{

float calculations::map(
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

}
