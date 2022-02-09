#include "leg_factory_impl.hpp"

#include "../hardware/servo_impl.hpp"
#include "../interpolation_impl.hpp"
#include "../../mathmatics/calculations.hpp"
#include "../../mathmatics/smoother_impl.hpp"
#include "../../mathmatics/trigonometry/isosceles_triangle_impl.hpp"
#include "../../mathmatics/trigonometry/right_angled_triangle_impl.hpp"
#include "../../robot/two_axis_leg.hpp"

namespace hal
{
namespace robot
{

std::unique_ptr<::robot::leg> leg_factory_impl::create(
    const ::robot::leg_type type,
    const std::shared_ptr<hal::hardware::arduino> arduino,
    const uint8_t shoulder_pin,
    const uint8_t knee_pin) const
{
    switch (type)
    {
        case ::robot::leg_type::two_axis:
        default:
        {
            std::unique_ptr<hal::hardware::servo> shoulder_servo{
                new hal::hardware::servo_impl()};
            std::unique_ptr<hal::hardware::servo> knee_servo{
                new hal::hardware::servo_impl()};
            std::unique_ptr<hal::interpolation> shoulder_interpolation{
                new hal::interpolation_impl()};
            std::unique_ptr<hal::interpolation> knee_interpolation{
                new hal::interpolation_impl()};
            std::unique_ptr<mathmatics::smoother> shoulder_smoother{
                new mathmatics::smoother_impl(arduino)};
            std::unique_ptr<mathmatics::smoother> knee_smoother{
                new mathmatics::smoother_impl(arduino)};

            return std::unique_ptr<::robot::leg>{
                new ::robot::two_axis_leg(
                    std::make_shared<
                        mathmatics::trigonometry::right_angled_triangle_impl>(),
                    std::make_shared<
                        mathmatics::trigonometry::isosceles_triangle_impl>(55),
                    std::move(shoulder_servo),
                    std::move(knee_servo),
                    std::move(shoulder_interpolation),
                    std::move(knee_interpolation),
                    std::move(shoulder_smoother),
                    std::move(knee_smoother),
                    std::make_shared<const mathmatics::calculations>(),
                    shoulder_pin,
                    knee_pin)};
        }
    }
}

}
}
