#ifndef CONTROLLER_CONTEXT_HPP
#define CONTROLLER_CONTEXT_HPP

#include <memory>

#include "../robot/robot_fwd.hpp"

#include "state_fwd.hpp"
#include "state_id.hpp"

namespace controller
{

class context
{
public:
    virtual ~context(){}

    virtual state& get_state() const = 0;

    virtual void set_state(state_id id) = 0;

    virtual std::shared_ptr<robot::robot> get_robot() = 0;

    virtual void set_gamepad_light_colour(
        uint8_t r, uint8_t g, uint8_t b) const = 0;

    virtual void small_rumble_controller(short milliseconds) const = 0;

    virtual void large_rumble_controller(short milliseconds) const = 0;
};

}

#endif
