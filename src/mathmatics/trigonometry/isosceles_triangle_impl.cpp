#include "isosceles_triangle_impl.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace mathmatics
{
namespace trigonometry
{

isosceles_triangle_impl::isosceles_triangle_impl(
    const uint8_t common_side_length) :
        common_side_length_(common_side_length)
{
}

std::tuple<float, float, float> isosceles_triangle_impl::generate_angles(
    const float side_c_length) const
{
    const float angle_a = acos(
        (side_c_length * side_c_length) /
            (2 * common_side_length_ * side_c_length));

    return std::make_tuple(angle_a, angle_a, M_PI - (angle_a * 2));
}

}
}
