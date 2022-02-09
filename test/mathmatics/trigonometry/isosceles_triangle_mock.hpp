#ifndef MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_MOCK_HPP
#define MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_MOCK_HPP

#include <gmock/gmock.h>
#include <mathmatics/trigonometry/isosceles_triangle.hpp>

namespace mathmatics
{
namespace trigonometry
{

class isosceles_triangle_mock : public isosceles_triangle
{
public:
    MOCK_METHOD(
        (std::tuple<float, float, float>),
        generate_angles,
        (float side_c_length),
        (const, override));
};

}
}

#endif
