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
    MOCK_CONST_METHOD2(generate_angles, std::tuple<float, float, float>(
        float side_a_length, float side_b_length));

    MOCK_CONST_METHOD2(calculate_hypotenuse, float(
        float side_a_length, float side_b_length));
};

}
}

#endif
