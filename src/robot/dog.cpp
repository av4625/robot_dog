#include "dog.hpp"
#include "../hal/config/manager.hpp"
#include "leg.hpp"

namespace robot
{

dog::dog(
    std::unique_ptr<leg> front_left,
    std::unique_ptr<leg> rear_left,
    std::unique_ptr<leg> front_right,
    std::unique_ptr<leg> rear_right,
    std::unique_ptr<hal::config::manager> config) :
        front_left_(std::move(front_left)),
        rear_left_(std::move(rear_left)),
        front_right_(std::move(front_right)),
        rear_right_(std::move(rear_right)),
        config_(std::move(config)),
        dog_settings_({})
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

void dog::set_position(const int8_t height, const int8_t forward_back)
{
    front_left_->set_position(
        height, forward_back, utility::robot::movement::smooth);
    rear_left_->set_position(
        height, forward_back, utility::robot::movement::smooth);
    front_right_->set_position(
        height, forward_back, utility::robot::movement::smooth);
    rear_right_->set_position(
        height, forward_back, utility::robot::movement::smooth);
}

void dog::set_height(const int8_t height)
{
    front_left_->set_height(height, utility::robot::movement::smooth);
    rear_left_->set_height(height, utility::robot::movement::smooth);
    front_right_->set_height(height, utility::robot::movement::smooth);
    rear_right_->set_height(height, utility::robot::movement::smooth);
}

void dog::set_forward_back(const int8_t forward_back)
{
    front_left_->set_forward_back(forward_back, utility::robot::movement::smooth);
    rear_left_->set_forward_back(forward_back, utility::robot::movement::smooth);
    front_right_->set_forward_back(forward_back, utility::robot::movement::smooth);
    rear_right_->set_forward_back(forward_back, utility::robot::movement::smooth);
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
}

void dog::set_legs_in_neutral_position()
{
    front_left_->set_leg_neutral_position();
    rear_left_->set_leg_neutral_position();
    front_right_->set_leg_neutral_position();
    rear_right_->set_leg_neutral_position();
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

}
