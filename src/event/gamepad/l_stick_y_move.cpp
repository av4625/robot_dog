#include "l_stick_y_move.hpp"

#include "../event_id.hpp"
#include "../../hal/event/event_base_id.hpp"

namespace event
{
namespace gamepad
{

l_stick_y_move::l_stick_y_move(const int8_t data) :
    data_(data)
{
}

const char* l_stick_y_move::get_event_base_id() const
{
    return hal::event::GAMEPAD_EVENTS;
}

int32_t l_stick_y_move::get_event_id() const
{
    return event_id::l_stick_y_move;
}

int8_t l_stick_y_move::get_data() const
{
    return data_;
}

}
}
