#include "leg_factory_impl.hpp"

#include "../hardware/servo_impl.hpp"
#include "../interpolation_impl.hpp"
#include "../../mathmatics/smoother_impl.hpp"
#include "../../mathmatics/trigonometry/isosceles_triangle_impl.hpp"
#include "../../mathmatics/trigonometry/right_angled_triangle_impl.hpp"
#include "../../robot/two_axis_leg.hpp"

namespace hal
{
namespace robot
{

std::unique_ptr<::robot::leg> leg_factory_impl::create(
    const utility::robot::leg_type type,
    const utility::robot::side side,
    const std::shared_ptr<hal::hardware::arduino> arduino,
    const std::shared_ptr<const mathmatics::calculations> calculations,
    const uint8_t shoulder_pin,
    const uint8_t knee_pin) const
{
    switch (type)
    {
        case utility::robot::leg_type::two_axis:
        default:
        {
            return std::unique_ptr<::robot::leg>{
                new ::robot::two_axis_leg(
                    std::make_shared<
                        mathmatics::trigonometry::right_angled_triangle_impl>(),
                    std::make_shared<
                        mathmatics::trigonometry::isosceles_triangle_impl>(55),
                    std::unique_ptr<hal::hardware::servo>{
                        new hal::hardware::servo_impl(shoulder_pin)},
                    std::unique_ptr<hal::hardware::servo>{
                        new hal::hardware::servo_impl(knee_pin)},
                    std::unique_ptr<hal::interpolation>{
                        new hal::interpolation_impl()},
                    std::unique_ptr<hal::interpolation>{
                        new hal::interpolation_impl()},
                    std::unique_ptr<mathmatics::smoother>{
                        new mathmatics::smoother_impl(arduino)},
                    std::unique_ptr<mathmatics::smoother>{
                        new mathmatics::smoother_impl(arduino)},
                    calculations,
                    side)};
        }
    }
}

}
}
