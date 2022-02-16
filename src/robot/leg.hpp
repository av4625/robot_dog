#ifndef ROBOT_LEG_HPP
#define ROBOT_LEG_HPP

#include <memory>
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/trigonometry/isosceles_triangle.hpp"
#include "../mathmatics/trigonometry/right_angled_triangle.hpp"
#include "movement.hpp"

namespace robot
{

class leg
{
public:
    virtual ~leg(){}
    virtual void begin() = 0;
    virtual void set_position(
        int8_t height, int8_t forward_back, movement move_type) = 0;
    virtual void set_height(int8_t height, movement move_type) = 0;
    virtual void set_forward_back(int8_t forward_back, movement move_type) = 0;
    virtual void update_position() = 0;
};

}

#endif
