#ifndef ROBOT_LEG_HPP
#define ROBOT_LEG_HPP

#include <memory>
#include "../hal/hardware/servo.hpp"
#include "../hal/interpolation.hpp"
#include "../mathmatics/calculations.hpp"
#include "../mathmatics/trigonometry/isosceles_triangle.hpp"
#include "../mathmatics/trigonometry/right_angled_triangle.hpp"
#include "../utility/robot/direction.hpp"
#include "../utility/robot/joint.hpp"
#include "../utility/robot/movement.hpp"

namespace robot
{

class leg
{
public:
    virtual ~leg(){}

    virtual void begin(short shoulder_trim, short knee_trim) = 0;

    virtual void set_position(
        int8_t height,
        int8_t forward_back,
        utility::robot::movement move_type) = 0;

    virtual void set_height(
        int8_t height, utility::robot::movement move_type) = 0;

    virtual void set_forward_back(
        int8_t forward_back, utility::robot::movement move_type) = 0;

    virtual bool update_position() = 0;

    virtual void set_leg_straight_down() = 0;

    virtual void set_leg_neutral_position() = 0;

    virtual short trim_joint(
        utility::robot::joint joint,
        utility::robot::direction direction) = 0;
};

}

#endif
