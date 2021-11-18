#ifndef ROBOT_LEG_HPP
#define ROBOT_LEG_HPP

#include <memory>
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/trigonometry/isosceles_triangle.hpp"
#include "../mathmatics/trigonometry/right_angled_triangle.hpp"

namespace robot
{

class leg
{
public:
    virtual ~leg(){}
    virtual void begin() = 0;
    virtual void set_position(int8_t height, int8_t forward_back) = 0;
    virtual void update_position() = 0;
};

}

#endif
