#ifndef MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_MOCK_HPP
#define MATHMATICS_TRIGONOMETRY_RIGHT_ANGLED_TRIANGLE_MOCK_HPP

#include <gmock/gmock.h>
#include <mathmatics/trigonometry/right_angled_triangle.hpp>

namespace mathmatics
{
namespace trigonometry
{

class right_angled_triangle_mock : public right_angled_triangle
{
public:
    MOCK_METHOD(
        (std::tuple<float, float, float>),
        generate_angles, (
        float side_a_length, float side_b_length),
        (const, override));

    MOCK_METHOD(
        float,
        calculate_hypotenuse, (
        float side_a_length, float side_b_length),
        (const, override));
};

}
}

#endif
