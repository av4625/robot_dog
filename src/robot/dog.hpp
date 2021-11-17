#ifndef ROBOT_DOG_HPP
#define ROBOT_DOG_HPP

#include "robot.hpp"

#include <memory>

#include "leg.hpp"

namespace robot
{

class dog : public robot
{
public:
    dog(
        std::unique_ptr<leg> front_left,
        std::unique_ptr<leg> rear_left,
        std::unique_ptr<leg> front_right,
        std::unique_ptr<leg> rear_right);

    void begin(
        uint8_t front_left_shoulder_pin, uint8_t front_left_knee_pin,
        uint8_t rear_left_shoulder_pin, uint8_t rear_left_knee_pin,
        uint8_t front_right_shoulder_pin, uint8_t front_right_knee_pin,
        uint8_t rear_right_shoulder_pin, uint8_t rear_right_knee_pin) override;

    void set_position(int8_t height, int8_t forward_back) override;

    void update_position() override;

private:
    const std::unique_ptr<leg> front_left_;
    const std::unique_ptr<leg> rear_left_;
    const std::unique_ptr<leg> front_right_;
    const std::unique_ptr<leg> rear_right_;
};

}

#endif
