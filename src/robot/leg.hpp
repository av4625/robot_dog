#ifndef ROBOT_LEG_HPP
#define ROBOT_LEG_HPP

#include <memory>
#include "../hal/hardware/servo.hpp"
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
            mathmatics::trigonometry::right_angled_triangle>& forward_back_triangle,
        const std::shared_ptr<
            mathmatics::trigonometry::isosceles_triangle>& height_triangle,
        std::unique_ptr<hal::hardware::servo> shoulder,
        std::unique_ptr<hal::hardware::servo> knee,
        const std::shared_ptr<mathmatics::calculations>& calc);

private:
    const std::shared_ptr<
        mathmatics::trigonometry::right_angled_triangle> forward_back_triangle_;
    const std::shared_ptr<
        mathmatics::trigonometry::isosceles_triangle> height_triangle_;
    const std::unique_ptr<hal::hardware::servo> shoulder_;
    const std::unique_ptr<hal::hardware::servo> knee_;
    const std::shared_ptr<mathmatics::calculations> calc_;
};

}

#endif
