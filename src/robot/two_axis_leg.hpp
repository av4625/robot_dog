#ifndef ROBOT_TWO_AXIS_LEG_HPP
#define ROBOT_TWO_AXIS_LEG_HPP

#include <memory>
#include "leg.hpp"
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/smoother.hpp"
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
        std::unique_ptr<mathmatics::smoother> shoulder_smoother,
        std::unique_ptr<mathmatics::smoother> knee_smoother,
        const std::shared_ptr<const mathmatics::calculations>& calc,
        uint8_t shoulder_pin,
        uint8_t knee_pin);

    void begin() override;

    void set_position(
        int8_t height,
        int8_t forward_back,
        utility::robot::movement move_type) override;

    void set_height(int8_t height, utility::robot::movement move_type) override;

    void set_forward_back(
        int8_t forward_back, utility::robot::movement move_type) override;

    bool update_position() override;

    void set_leg_straight_down() override;

    void set_leg_neutral_position() override;

    void trim_joint(
        utility::robot::joint joint,
        utility::robot::direction direction) override;

private:
    const std::shared_ptr<
        const mathmatics::trigonometry::right_angled_triangle> forward_back_triangle_;
    const std::shared_ptr<
        const mathmatics::trigonometry::isosceles_triangle> height_triangle_;
    const std::unique_ptr<hal::hardware::servo> shoulder_;
    const std::unique_ptr<hal::hardware::servo> knee_;
    const std::unique_ptr<hal::interpolation> shoulder_interpolation_;
    const std::unique_ptr<hal::interpolation> knee_interpolation_;
    const std::unique_ptr<mathmatics::smoother> shoulder_smoother_;
    const std::unique_ptr<mathmatics::smoother> knee_smoother_;
    const std::shared_ptr<const mathmatics::calculations> calc_;
    const uint8_t shoulder_pin_;
    const uint8_t knee_pin_;
    const short minimum_time_for_max_rotation_;
    const uint8_t max_height_;
    const uint8_t min_height_;
    const int8_t max_forward_;
    const int8_t max_back_;

    short previous_shoulder_microseconds_;
    short previous_knee_microseconds_;
    int8_t previous_forward_back_;
    int8_t previous_height_;
    utility::robot::movement current_move_type_;
    short shoulder_trim_offset_microseconds_;
    short knee_trim_offset_microseconds_;
    short min_servo_microseconds_shoulder_;
    short max_servo_microseconds_shoulder_;
    short min_servo_microseconds_knee_;
    short max_servo_microseconds_knee_;

    std::pair<float, float> generate_angles(
        int8_t height, int8_t forward_back) const;

    std::pair<short, short> calculate_servo_microseconds(
        float shoulder_angle, float knee_angle) const;

    void set_new_servo_positions_interpolation(
        short shoulder_microseconds, short knee_microseconds);

    void set_new_servo_positions_smooth(
        short shoulder_microseconds, short knee_microseconds);

    bool update_interpolation();

    bool update_smooth();

    void move_to_position(utility::robot::joint joint, short microseconds);
};

}

#endif
