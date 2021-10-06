#ifndef MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_IMPL_HPP
#define MATHMATICS_TRIGONOMETRY_ISOSCELES_TRIANGLE_IMPL_HPP

#include <cstdint>
#include "isosceles_triangle.hpp"

namespace mathmatics
{
namespace trigonometry
{

class isosceles_triangle_impl : public isosceles_triangle
{
public:
    explicit isosceles_triangle_impl(uint8_t common_side_length);

    std::tuple<float, float, float> generate_angles(
        float side_c_length) const override;

private:
    const uint8_t common_side_length_;
};

}
}

#endif
