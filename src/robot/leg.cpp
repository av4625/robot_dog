#include "leg.hpp"

namespace robot
{

leg::leg(
    const std::shared_ptr<
        const mathmatics::trigonometry::right_angled_triangle>& forward_back_triangle,
    const std::shared_ptr<
        const mathmatics::trigonometry::isosceles_triangle>& height_triangle,
    std::unique_ptr<hal::hardware::servo> shoulder,
    std::unique_ptr<hal::hardware::servo> knee,
    std::unique_ptr<hal::interpolation> shoulder_interpolation,
    std::unique_ptr<hal::interpolation> knee_interpolation,
    const std::shared_ptr<const mathmatics::calculations>& calc) :
        forward_back_triangle_(forward_back_triangle),
        height_triangle_(height_triangle),
        shoulder_(std::move(shoulder)),
        knee_(std::move(knee)),
        shoulder_interpolation_(std::move(shoulder_interpolation)),
        knee_interpolation_(std::move(knee_interpolation)),
        calc_(calc)
{
}

}
