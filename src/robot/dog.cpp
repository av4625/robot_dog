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

void dog::begin()
{
    front_left_->begin();
    rear_left_->begin();
    front_right_->begin();
    rear_right_->begin();
}

void dog::set_position(const int8_t height, const int8_t forward_back)
{
    front_left_->set_position(height, forward_back, movement::smooth);
    rear_left_->set_position(height, forward_back, movement::smooth);
    front_right_->set_position(height, forward_back, movement::smooth);
    rear_right_->set_position(height, forward_back, movement::smooth);
}

void dog::set_height(const int8_t height)
{
    front_left_->set_height(height, movement::smooth);
    rear_left_->set_height(height, movement::smooth);
    front_right_->set_height(height, movement::smooth);
    rear_right_->set_height(height, movement::smooth);
}

void dog::set_forward_back(const int8_t forward_back)
{
    front_left_->set_forward_back(forward_back, movement::smooth);
    rear_left_->set_forward_back(forward_back, movement::smooth);
    front_right_->set_forward_back(forward_back, movement::smooth);
    rear_right_->set_forward_back(forward_back, movement::smooth);
}

bool dog::update_position()
{
    const bool front_left{front_left_->update_position()};
    const bool rear_left{rear_left_->update_position()};
    const bool front_right{front_right_->update_position()};
    const bool rear_right{rear_right_->update_position()};

    return front_left && rear_left && front_right && rear_right;
}

}
