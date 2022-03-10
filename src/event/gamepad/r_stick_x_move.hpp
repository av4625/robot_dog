#ifndef EVENT_GAMEPAD_R_STICK_X_MOVE_HPP
#define EVENT_GAMEPAD_R_STICK_X_MOVE_HPP

#include "../event.hpp"

namespace event
{
namespace gamepad
{

class r_stick_x_move : public event
{
public:
    const char* get_event_base_id() const override;

    int32_t get_event_id() const override;
};

}
}

#endif
