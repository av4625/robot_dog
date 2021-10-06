#ifndef MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_IMPL_HPP
#define MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_IMPL_HPP

#include "right_angled_triangle.hpp"

namespace mathmatics
{
namespace trigonometry
{

class right_angled_triangle_impl : public right_angled_triangle
{
public:
    std::tuple<float, float, float> generate_angles(
        float side_a_length, float side_b_length) const override;

    float calculate_hypotenuse(
        float side_a_length, float side_b_length) const override;
};

}
}

#endif
