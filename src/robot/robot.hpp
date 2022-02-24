#ifndef ROBOT_ROBOT_HPP
#define ROBOT_ROBOT_HPP

#include <cstdint>

#include "../utility/robot/direction.hpp"
#include "../utility/robot/joint.hpp"
#include "../utility/robot/limb.hpp"

namespace robot
{

class robot
{
public:
    virtual ~robot(){}
    virtual void begin() = 0;
    virtual void set_position(int8_t height, int8_t forward_back) = 0;
    virtual void set_height(int8_t height) = 0;
    virtual void set_forward_back(int8_t forward_back) = 0;
    virtual bool update_position() = 0;
    virtual void fully_extend_legs() = 0;
    virtual void set_legs_in_neutral_position() = 0;
    virtual void trim_joint(
        utility::robot::limb limb,
        utility::robot::joint joint,
        utility::robot::direction direction) = 0;
    virtual void save_trim_values() = 0;
};

}

#endif
