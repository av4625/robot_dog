#include "dog.hpp"

namespace robot
{

dog::dog(
    std::unique_ptr<leg> front_left,
    std::unique_ptr<leg> rear_left,
    std::unique_ptr<leg> front_right,
    std::unique_ptr<leg> rear_right) :
        front_left_(std::move(front_left)),
        rear_left_(std::move(rear_left)),
        front_right_(std::move(front_right)),
        rear_right_(std::move(rear_right))
{
}

void dog::begin(
    const uint8_t front_left_shoulder_pin, const uint8_t front_left_knee_pin,
    const uint8_t rear_left_shoulder_pin, const uint8_t rear_left_knee_pin,
    const uint8_t front_right_shoulder_pin, const uint8_t front_right_knee_pin,
    const uint8_t rear_right_shoulder_pin, const uint8_t rear_right_knee_pin)
{
    front_left_->begin(front_left_shoulder_pin, front_left_knee_pin);
    rear_left_->begin(rear_left_shoulder_pin, rear_left_knee_pin);
    front_right_->begin(front_right_shoulder_pin, front_right_knee_pin);
    rear_right_->begin(rear_right_shoulder_pin, rear_right_knee_pin);
}

void dog::set_position(const int8_t height, const int8_t forward_back)
{
    front_left_->set_position(height, forward_back);
    rear_left_->set_position(height, forward_back);
    front_right_->set_position(height, forward_back);
    rear_right_->set_position(height, forward_back);
}

void dog::update_position()
{
    front_left_->update_position();
    rear_left_->update_position();
    front_right_->update_position();
    rear_right_->update_position();
}

}
