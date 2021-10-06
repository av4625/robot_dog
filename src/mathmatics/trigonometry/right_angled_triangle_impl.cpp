#include "right_angled_triangle_impl.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

namespace mathmatics
{
namespace trigonometry
{

std::tuple<float, float, float> right_angled_triangle_impl::generate_angles(
    float side_a_length, float side_b_length) const
{
    const float angle_a = atan(side_a_length / side_b_length);
    const float angle_c = M_PI / 2;
    return std::make_tuple(angle_a, M_PI - (angle_a + angle_c), angle_c);
}

float right_angled_triangle_impl::calculate_hypotenuse(
    float side_a_length, float side_b_length) const
{
    return sqrt(
        (side_a_length * side_a_length) + (side_b_length * side_b_length));
}

}
}
