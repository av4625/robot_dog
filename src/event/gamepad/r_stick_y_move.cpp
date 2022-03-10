#include "r_stick_y_move.hpp"

#include "../event_id.hpp"
#include "../../hal/event/event_base_id.hpp"

namespace event
{
namespace gamepad
{

const char* r_stick_y_move::get_event_base_id() const
{
    return hal::event::GAMEPAD_EVENTS;
}

int32_t r_stick_y_move::get_event_id() const
{
    return event_id::r_stick_y_move;
}

}
}
