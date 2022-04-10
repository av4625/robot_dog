#include "dog.hpp"

#include <cmath>

#include "../hal/config/manager.hpp"
#include "leg.hpp"

namespace robot
{

dog::dog(
    std::unique_ptr<leg> front_left,
    std::unique_ptr<leg> rear_left,
    std::unique_ptr<leg> front_right,
    std::unique_ptr<leg> rear_right,
    std::unique_ptr<hal::config::manager> config,
    const std::shared_ptr<const mathmatics::calculations>& calc) :
        front_left_(std::move(front_left)),
        rear_left_(std::move(rear_left)),
        front_right_(std::move(front_right)),
        rear_right_(std::move(rear_right)),
        config_(std::move(config)),
        calc_(calc),
        dog_settings_({}),
        previous_height_(0),
        previous_forward_back_lean_(0),
        previous_side_to_side_lean_(0)
{
}

void dog::begin()
{
    config_->begin();
    config_->get_settings(dog_settings_);

    front_left_->begin(
        dog_settings_.front_left_shoulder, dog_settings_.front_left_knee);
    rear_left_->begin(
        dog_settings_.rear_left_shoulder, dog_settings_.rear_left_knee);
    front_right_->begin(
        dog_settings_.front_right_shoulder, dog_settings_.front_right_knee);
    rear_right_->begin(
        dog_settings_.rear_right_shoulder, dog_settings_.rear_right_knee);
}

void dog::set_position(
    const int8_t height,
    const int8_t forward_back,
    const int8_t forward_back_lean,
    const int8_t side_to_side_lean)
{
    front_left_->set_position(
        calculate_leg_height(
            utility::robot::limb::front_left,
            height,
            forward_back_lean,
            side_to_side_lean),
        forward_back,
        utility::robot::movement::smooth);

    rear_left_->set_position(
        calculate_leg_height(
            utility::robot::limb::rear_left,
            height,
            forward_back_lean,
            side_to_side_lean),
        forward_back,
        utility::robot::movement::smooth);

    front_right_->set_position(
        calculate_leg_height(
            utility::robot::limb::front_right,
            height,
            forward_back_lean,
            side_to_side_lean),
        forward_back,
        utility::robot::movement::smooth);

    rear_right_->set_position(
        calculate_leg_height(
            utility::robot::limb::rear_right,
            height,
            forward_back_lean,
            side_to_side_lean),
        forward_back,
        utility::robot::movement::smooth);

    previous_height_ = height;
    previous_forward_back_lean_ = forward_back_lean;
    previous_side_to_side_lean_ = side_to_side_lean;
}

void dog::set_height(const int8_t height)
{
    front_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_left,
            height,
            previous_forward_back_lean_,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    rear_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_left,
            height,
            previous_forward_back_lean_,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    front_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_right,
            height,
            previous_forward_back_lean_,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    rear_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_right,
            height,
            previous_forward_back_lean_,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    previous_height_ = height;
}

void dog::set_forward_back(const int8_t forward_back)
{
    front_left_->set_forward_back(
        forward_back, utility::robot::movement::smooth);
    rear_left_->set_forward_back(
        forward_back, utility::robot::movement::smooth);
    front_right_->set_forward_back(
        forward_back, utility::robot::movement::smooth);
    rear_right_->set_forward_back(
        forward_back, utility::robot::movement::smooth);
}

void dog::set_forward_back_lean(const int8_t lean)
{
    front_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_left,
            previous_height_,
            lean,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    rear_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_left,
            previous_height_,
            lean,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    front_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_right,
            previous_height_,
            lean,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    rear_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_right,
            previous_height_,
            lean,
            previous_side_to_side_lean_),
        utility::robot::movement::smooth);

    previous_forward_back_lean_ = lean;
}

void dog::set_side_to_side_lean(const int8_t lean)
{
    front_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_left,
            previous_height_,
            previous_forward_back_lean_,
            lean),
        utility::robot::movement::smooth);

    rear_left_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_left,
            previous_height_,
            previous_forward_back_lean_,
            lean),
        utility::robot::movement::smooth);

    front_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::front_right,
            previous_height_,
            previous_forward_back_lean_,
            lean),
        utility::robot::movement::smooth);

    rear_right_->set_height(
        calculate_leg_height(
            utility::robot::limb::rear_right,
            previous_height_,
            previous_forward_back_lean_,
            lean),
        utility::robot::movement::smooth);

    previous_side_to_side_lean_ = lean;
}

bool dog::update_position()
{
    const bool front_left{front_left_->update_position()};
    const bool rear_left{rear_left_->update_position()};
    const bool front_right{front_right_->update_position()};
    const bool rear_right{rear_right_->update_position()};

    return front_left && rear_left && front_right && rear_right;
}

void dog::fully_extend_legs()
{
    front_left_->set_leg_straight_down();
    rear_left_->set_leg_straight_down();
    front_right_->set_leg_straight_down();
    rear_right_->set_leg_straight_down();

    previous_height_ = 0;
    previous_forward_back_lean_ = 0;
    previous_side_to_side_lean_ = 0;
}

void dog::set_legs_in_neutral_position()
{
    front_left_->set_leg_neutral_position();
    rear_left_->set_leg_neutral_position();
    front_right_->set_leg_neutral_position();
    rear_right_->set_leg_neutral_position();

    previous_height_ = 0;
    previous_forward_back_lean_ = 0;
    previous_side_to_side_lean_ = 0;
}

void dog::trim_joint(
    const utility::robot::limb limb,
    const utility::robot::joint joint,
    const utility::robot::direction direction)
{
    switch (limb)
    {
        case utility::robot::limb::front_left:
        {
            const short trim{front_left_->trim_joint(joint, direction)};

            if (joint == utility::robot::joint::shoulder)
            {
                dog_settings_.front_left_shoulder = trim;
            }
            else if (joint == utility::robot::joint::knee)
            {
                dog_settings_.front_left_knee = trim;
            }

            break;
        }
        case utility::robot::limb::rear_left:
        {
            const short trim{rear_left_->trim_joint(joint, direction)};

            if (joint == utility::robot::joint::shoulder)
            {
                dog_settings_.rear_left_shoulder = trim;
            }
            else if (joint == utility::robot::joint::knee)
            {
                dog_settings_.rear_left_knee = trim;
            }

            break;
        }
        case utility::robot::limb::front_right:
        {
            const short trim{front_right_->trim_joint(joint, direction)};

            if (joint == utility::robot::joint::shoulder)
            {
                dog_settings_.front_right_shoulder = trim;
            }
            else if (joint == utility::robot::joint::knee)
            {
                dog_settings_.front_right_knee = trim;
            }

            break;
        }
        case utility::robot::limb::rear_right:
        {
            const short trim{rear_right_->trim_joint(joint, direction)};

            if (joint == utility::robot::joint::shoulder)
            {
                dog_settings_.rear_right_shoulder = trim;
            }
            else if (joint == utility::robot::joint::knee)
            {
                dog_settings_.rear_right_knee = trim;
            }

            break;
        }
    }
}

void dog::save_trim_values()
{
    config_->save_settings(dog_settings_);
}

int8_t dog::calculate_leg_height(
    const utility::robot::limb limb,
    const int8_t height,
    const int8_t forward_back_lean,
    const int8_t side_to_side_lean) const
{
    /* int so I don't get rollover when calculating and so I don't have to cast
       for constrict */
    int new_height{height};

    if (limb == utility::robot::limb::front_left ||
        limb == utility::robot::limb::front_right)
    {
        new_height -= forward_back_lean;
    }
    else
    {
        new_height += forward_back_lean;
    }

    if (limb == utility::robot::limb::front_left ||
        limb == utility::robot::limb::rear_left)
    {
        new_height += side_to_side_lean;
    }
    else
    {
        new_height -= side_to_side_lean;
    }

    new_height = calc_->constrict(new_height, INT8_MIN, INT8_MAX);

    return static_cast<int8_t>(new_height);
}

}
