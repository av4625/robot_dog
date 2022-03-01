#include "two_axis_leg.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>

namespace robot
{

namespace
{

const double zero_degrees_radians{0};
const double forty_five_degrees_radians{M_PI / 4};
const double ninety_degrees_radians{M_PI / 2};
const double one_hundred_and_thirty_five_degrees_radians{
    M_PI - forty_five_degrees_radians};
const double one_hundred_and_eighty_degrees_radians{M_PI};

const short min_servo_microseconds{500};
const short max_servo_microseconds{2500};

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
        current_move_type_(utility::robot::movement::interpolation),
        shoulder_trim_offset_microseconds_(0),
        knee_trim_offset_microseconds_(0),
        min_servo_microseconds_shoulder_(min_servo_microseconds),
        max_servo_microseconds_shoulder_(max_servo_microseconds),
        min_servo_microseconds_knee_(min_servo_microseconds),
        max_servo_microseconds_knee_(max_servo_microseconds),
        has_position_changed_(true)
{
}

void two_axis_leg::begin(const short shoulder_trim, const short knee_trim)
{
    shoulder_->begin(shoulder_pin_);
    knee_->begin(knee_pin_);

    shoulder_trim_offset_microseconds_ = shoulder_trim;
    knee_trim_offset_microseconds_ = knee_trim;

    min_servo_microseconds_shoulder_ =
        min_servo_microseconds + shoulder_trim_offset_microseconds_;
    max_servo_microseconds_shoulder_ =
        max_servo_microseconds + shoulder_trim_offset_microseconds_;
    min_servo_microseconds_knee_ =
        min_servo_microseconds + knee_trim_offset_microseconds_;
    max_servo_microseconds_knee_ =
        max_servo_microseconds + knee_trim_offset_microseconds_;
}

void two_axis_leg::set_position(
    const int8_t height,
    const int8_t forward_back,
    const utility::robot::movement move_type)
{
    current_move_type_ = move_type;

    if (height != previous_height_ ||
        forward_back != previous_forward_back_ ||
        has_position_changed_)
    {
        const auto angles{generate_angles(height, forward_back)};

        const auto microseconds{
            calculate_servo_microseconds(angles.first, angles.second)};

        switch (move_type)
        {
            case utility::robot::movement::smooth:
            {
                set_new_servo_positions_smooth(
                    microseconds.first, microseconds.second);
                break;
            }
            case utility::robot::movement::interpolation:
            {
                set_new_servo_positions_interpolation(
                    microseconds.first, microseconds.second);
                break;
            }
            default:
            {
                set_new_servo_positions_smooth(
                    microseconds.first, microseconds.second);
                break;
            }
        }

        previous_height_ = height;
        previous_forward_back_ = forward_back;
        has_position_changed_ = false;
    }
}

void two_axis_leg::set_height(
    const int8_t height, const utility::robot::movement move_type)
{
    set_position(height, previous_forward_back_, move_type);
}

void two_axis_leg::set_forward_back(
    const int8_t forward_back, const utility::robot::movement move_type)
{
    set_position(previous_height_, forward_back, move_type);
}

bool two_axis_leg::update_position()
{
    switch (current_move_type_)
    {
        case utility::robot::movement::smooth:
        {
            return update_smooth();
        }
        case utility::robot::movement::interpolation:
        {
            return update_interpolation();
        }
        default:
        {
            return update_smooth();
        }
    }
}

void two_axis_leg::set_leg_straight_down()
{
    has_position_changed_ = true;

    const auto servo_values{
        calculate_servo_microseconds(
            zero_degrees_radians, one_hundred_and_eighty_degrees_radians)};
    set_new_servo_positions_smooth(servo_values.first, servo_values.second);
}

void two_axis_leg::set_leg_neutral_position()
{
    set_position(0, 0, utility::robot::movement::smooth);
}

short two_axis_leg::trim_joint(
    const utility::robot::joint joint,
    const utility::robot::direction direction)
{
    has_position_changed_ = true;

    if (joint == utility::robot::joint::shoulder)
    {
        if (direction == utility::robot::direction::clockwise)
        {
            shoulder_trim_offset_microseconds_ += 10;
            move_to_position(joint, previous_shoulder_microseconds_ += 10);
        }
        else
        {
            shoulder_trim_offset_microseconds_ -= 10;
            move_to_position(joint, previous_shoulder_microseconds_ -= 10);
        }

        min_servo_microseconds_shoulder_ =
            min_servo_microseconds + shoulder_trim_offset_microseconds_;
        max_servo_microseconds_shoulder_ =
            max_servo_microseconds + shoulder_trim_offset_microseconds_;

        return shoulder_trim_offset_microseconds_;
    }
    else
    {
        if (direction == utility::robot::direction::clockwise)
        {
            knee_trim_offset_microseconds_ += 10;
            move_to_position(joint, previous_knee_microseconds_ += 10);
        }
        else
        {
            knee_trim_offset_microseconds_ -= 10;
            move_to_position(joint, previous_knee_microseconds_ -= 10);
        }

        min_servo_microseconds_knee_ =
            min_servo_microseconds + knee_trim_offset_microseconds_;
        max_servo_microseconds_knee_ =
            max_servo_microseconds + knee_trim_offset_microseconds_;

        return knee_trim_offset_microseconds_;
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
        calc_->constrict(
            static_cast<short>(calc_->map(
                shoulder_angle,
                -forty_five_degrees_radians,
                one_hundred_and_thirty_five_degrees_radians,
                min_servo_microseconds_shoulder_,
                max_servo_microseconds_shoulder_)),
            min_servo_microseconds,
            max_servo_microseconds),
        calc_->constrict(
            static_cast<short>(calc_->map(
                knee_angle,
                zero_degrees_radians,
                one_hundred_and_eighty_degrees_radians,
                max_servo_microseconds_knee_,
                min_servo_microseconds_knee_)),
            min_servo_microseconds,
            max_servo_microseconds));
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

bool two_axis_leg::update_interpolation()
{
    if (!shoulder_interpolation_->is_finished() ||
        !knee_interpolation_->is_finished())
    {
        previous_shoulder_microseconds_ = shoulder_interpolation_->get_value();
        previous_knee_microseconds_ = knee_interpolation_->get_value();
        shoulder_->write_microseconds(previous_shoulder_microseconds_);
        knee_->write_microseconds(previous_knee_microseconds_);

        return shoulder_interpolation_->is_finished() &&
            knee_interpolation_->is_finished();
    }

    return true;
}

bool two_axis_leg::update_smooth()
{
    if (!shoulder_smoother_->is_finished() ||
        !knee_smoother_->is_finished())
    {
        previous_shoulder_microseconds_ = shoulder_smoother_->get_value();
        previous_knee_microseconds_ = knee_smoother_->get_value();
        shoulder_->write_microseconds(previous_shoulder_microseconds_);
        knee_->write_microseconds(previous_knee_microseconds_);

        return shoulder_smoother_->is_finished() &&
            knee_smoother_->is_finished();
    }

    return true;
}

void two_axis_leg::move_to_position(
    const utility::robot::joint joint, const short microseconds)
{
    if (joint == utility::robot::joint::shoulder)
    {
        previous_shoulder_microseconds_ = microseconds;
        shoulder_->write_microseconds(microseconds);
    }
    else
    {
        previous_knee_microseconds_ = microseconds;
        knee_->write_microseconds(microseconds);
    }
}

}
