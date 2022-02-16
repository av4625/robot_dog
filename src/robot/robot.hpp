#ifndef ROBOT_ROBOT_HPP
#define ROBOT_ROBOT_HPP

#include <cstdint>

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
    virtual void update_position() = 0;
};

}

#endif
