#ifndef ROBOT_LEG_HPP
#define ROBOT_LEG_HPP

#include <memory>
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/trigonometry/isosceles_triangle.hpp"
#include "../mathmatics/trigonometry/right_angled_triangle.hpp"

namespace robot
{

class leg
{
public:
    leg(
        const std::shared_ptr<
            const mathmatics::trigonometry::right_angled_triangle>& forward_back_triangle,
        const std::shared_ptr<
            const mathmatics::trigonometry::isosceles_triangle>& height_triangle,
        std::unique_ptr<hal::hardware::servo> shoulder,
        std::unique_ptr<hal::hardware::servo> knee,
        std::unique_ptr<hal::interpolation> shoulder_interpolation,
        std::unique_ptr<hal::interpolation> knee_interpolation,
        const std::shared_ptr<const mathmatics::calculations>& calc);

private:
    const std::shared_ptr<
        const mathmatics::trigonometry::right_angled_triangle> forward_back_triangle_;
    const std::shared_ptr<
        const mathmatics::trigonometry::isosceles_triangle> height_triangle_;
    const std::unique_ptr<hal::hardware::servo> shoulder_;
    const std::unique_ptr<hal::hardware::servo> knee_;
    const std::unique_ptr<hal::interpolation> shoulder_interpolation_;
    const std::unique_ptr<hal::interpolation> knee_interpolation_;
    const std::shared_ptr<const mathmatics::calculations> calc_;
};

}

#endif
