#ifndef ROBOT_TWO_AXIS_LEG_HPP
#define ROBOT_TWO_AXIS_LEG_HPP

#include <memory>
#include "leg.hpp"
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/trigonometry/isosceles_triangle.hpp"
#include "../mathmatics/trigonometry/right_angled_triangle.hpp"

namespace robot
{

class two_axis_leg : public leg
{
public:
    two_axis_leg(
        const std::shared_ptr<
            const mathmatics::trigonometry::right_angled_triangle>& forward_back_triangle,
        const std::shared_ptr<
            const mathmatics::trigonometry::isosceles_triangle>& height_triangle,
        std::unique_ptr<hal::hardware::servo> shoulder,
        std::unique_ptr<hal::hardware::servo> knee,
        std::unique_ptr<hal::interpolation> shoulder_interpolation,
        std::unique_ptr<hal::interpolation> knee_interpolation,
        const std::shared_ptr<const mathmatics::calculations>& calc);

    void begin(uint8_t shoulder_pin, uint8_t knee_pin) override;

    void set_position(int8_t height, int8_t forward_back) override;

    void update_position() override;

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
    const short minimum_time_for_max_rotation_;
    const uint8_t max_height_;
    const uint8_t min_height_;
    const int8_t max_forward_;
    const int8_t max_back_;

    short previous_shoulder_microseconds_;
    short previous_knee_microseconds_;
    int8_t previous_forward_back_;
    int8_t previous_height_;

    void set_new_servo_positions(float shoulder_angle, float knee_angle);
};

}

#endif
