#include "two_axis_leg.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>

namespace robot
{

namespace
{
const float right_angle_radians{M_PI / 2};
}

two_axis_leg::two_axis_leg(
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
    const uint8_t shoulder_pin,
    const uint8_t knee_pin) :
        forward_back_triangle_(forward_back_triangle),
        height_triangle_(height_triangle),
        shoulder_(std::move(shoulder)),
        knee_(std::move(knee)),
        shoulder_interpolation_(std::move(shoulder_interpolation)),
        knee_interpolation_(std::move(knee_interpolation)),
        shoulder_smoother_(std::move(shoulder_smoother)),
        knee_smoother_(std::move(knee_smoother)),
        calc_(calc),
        shoulder_pin_(shoulder_pin),
        knee_pin_(knee_pin),
        minimum_time_for_max_rotation_(
            (shoulder_->get_minimum_time_for_180() > knee_->get_minimum_time_for_180()) ?
                shoulder_->get_minimum_time_for_180() :
                    knee_->get_minimum_time_for_180()),
        max_height_(95),
        min_height_(40),
        max_forward_(-30),
        max_back_(30),
        previous_shoulder_microseconds_(1500),
        previous_knee_microseconds_(1500),
        previous_forward_back_(0),
        previous_height_(0),
        current_move_type_(movement::interpolation)
{
}

void two_axis_leg::begin()
{
    shoulder_->begin(shoulder_pin_);
    knee_->begin(knee_pin_);
}

void two_axis_leg::set_position(
    const int8_t height, const int8_t forward_back, const movement move_type)
{
    current_move_type_ = move_type;

    if (height != previous_height_ || forward_back != previous_forward_back_)
    {
        const auto angles{generate_angles(height, forward_back)};

        const auto microseconds{
            calculate_servo_microseconds(angles.first, angles.second)};

        switch (move_type)
        {
            case movement::smooth:
                set_new_servo_positions_smooth(
                    microseconds.first, microseconds.second);
                break;
            case movement::interpolation:
                set_new_servo_positions_interpolation(
                    microseconds.first, microseconds.second);
                break;
            default:
                set_new_servo_positions_smooth(
                    microseconds.first, microseconds.second);
                break;
        }

        previous_height_ = height;
        previous_forward_back_ = forward_back;
    }
}

void two_axis_leg::update_position()
{
    switch (current_move_type_)
    {
        case movement::smooth:
            update_smooth();
            break;
        case movement::interpolation:
            update_interpolation();
            break;
        default:
            update_smooth();
            break;
    }
}

std::pair<float, float> two_axis_leg::generate_angles(
    const int8_t height, const int8_t forward_back) const
{
    const uint8_t height_mm = calc_->map(
        height, INT8_MIN, INT8_MAX, min_height_, max_height_);
    const int8_t forward_back_mm = calc_->map(
        forward_back, INT8_MIN, INT8_MAX, max_forward_, max_back_);

    const auto leg_height = forward_back_triangle_->calculate_hypotenuse(
        forward_back_mm, height_mm);
    const auto shoulder_advance = forward_back_triangle_->generate_angles(
        forward_back_mm, height_mm);

    const auto angles = height_triangle_->generate_angles(leg_height);

    const float shoulder_angle =
        std::get<0>(angles) + std::get<0>(shoulder_advance);

    return std::make_pair(shoulder_angle, std::get<2>(angles));
}

std::pair<short, short> two_axis_leg::calculate_servo_microseconds(
    const float shoulder_angle, const float knee_angle) const
{
    return std::make_pair(
        calc_->map(
            shoulder_angle, -right_angle_radians, right_angle_radians, 40, 2040),
        calc_->map(knee_angle, 0, M_PI, 2600, 600));
}

void two_axis_leg::set_new_servo_positions_interpolation(
    const short shoulder_microseconds, const short knee_microseconds)
{
    /**
     * Find difference in microseconds from the previous movement to the current.
     * Max difference can be 2000 (2500 - 500).
     * Minimum movement time for the servo to go from 500 to 2500 is 500 milliseconds.
     * Divide by 4 to get the time for the movement.
     */
    const short knee_movement_time{
        static_cast<short>(
            fabs(knee_microseconds - previous_knee_microseconds_) / 4)};
    const short shoulder_movement_time{
        static_cast<short>(
            fabs(shoulder_microseconds - previous_shoulder_microseconds_) / 4)};

    const short movement_time{
        (knee_movement_time > shoulder_movement_time) ?
            knee_movement_time : shoulder_movement_time};

    shoulder_interpolation_->start(
        previous_shoulder_microseconds_,
        shoulder_microseconds,
        movement_time,
        hal::interpolation_curve::SINUSOIDAL_OUT);

    previous_shoulder_microseconds_ = shoulder_interpolation_->get_value();
    shoulder_->write_microseconds(previous_shoulder_microseconds_);

    knee_interpolation_->start(
        previous_knee_microseconds_,
        knee_microseconds,
        movement_time,
        hal::interpolation_curve::SINUSOIDAL_OUT);

    previous_knee_microseconds_ = knee_interpolation_->get_value();
    knee_->write_microseconds(previous_knee_microseconds_);
}

void two_axis_leg::set_new_servo_positions_smooth(
    const short shoulder_microseconds, const short knee_microseconds)
{
    shoulder_smoother_->start(
        previous_shoulder_microseconds_, shoulder_microseconds);
    knee_smoother_->start(
        previous_knee_microseconds_, knee_microseconds);

    previous_shoulder_microseconds_ = shoulder_smoother_->get_value();
    previous_knee_microseconds_ = knee_smoother_->get_value();

    shoulder_->write_microseconds(previous_shoulder_microseconds_);
    knee_->write_microseconds(previous_knee_microseconds_);
}

void two_axis_leg::update_interpolation()
{
    if (!shoulder_interpolation_->is_finished() ||
        !knee_interpolation_->is_finished())
    {
        previous_shoulder_microseconds_ = shoulder_interpolation_->get_value();
        previous_knee_microseconds_ = knee_interpolation_->get_value();
        shoulder_->write_microseconds(previous_shoulder_microseconds_);
        knee_->write_microseconds(previous_knee_microseconds_);
    }
}

void two_axis_leg::update_smooth()
{
    if (!shoulder_smoother_->is_finished() ||
        !knee_smoother_->is_finished())
    {
        previous_shoulder_microseconds_ = shoulder_smoother_->get_value();
        previous_knee_microseconds_ = knee_smoother_->get_value();
        shoulder_->write_microseconds(previous_shoulder_microseconds_);
        knee_->write_microseconds(previous_knee_microseconds_);
    }
}

}
