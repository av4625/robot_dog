#ifndef ROBOT_ROBOT_HPP
#define ROBOT_ROBOT_HPP

#include <cstdint>

namespace robot
{

class robot
{
public:
    virtual ~robot(){}
    virtual void begin(
        uint8_t front_left_shoulder_pin, uint8_t front_left_knee_pin,
        uint8_t rear_left_shoulder_pin, uint8_t rear_left_knee_pin,
        uint8_t front_right_shoulder_pin, uint8_t front_right_knee_pin,
        uint8_t rear_right_shoulder_pin, uint8_t rear_right_knee_pin) = 0;
    virtual void set_position(int8_t height, int8_t forward_back) = 0;
    virtual void update_position() = 0;
};

}

#endif
