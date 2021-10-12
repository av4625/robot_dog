#include "leg.hpp"

namespace robot
{

leg::leg(
    const std::shared_ptr<
        mathmatics::trigonometry::right_angled_triangle>& forward_back_triangle,
    const std::shared_ptr<
        mathmatics::trigonometry::isosceles_triangle>& height_triangle,
    std::unique_ptr<hal::hardware::servo> shoulder,
    std::unique_ptr<hal::hardware::servo> knee,
    const std::shared_ptr<mathmatics::calculations>& calc) :
        forward_back_triangle_(forward_back_triangle),
        height_triangle_(height_triangle),
        shoulder_(std::move(shoulder)),
        knee_(std::move(knee)),
        calc_(calc)
{
}

}
