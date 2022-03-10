#include "right_button.hpp"

#include "../event_id.hpp"
#include "../../hal/event/event_base_id.hpp"

namespace event
{
namespace gamepad
{

const char* right_button::get_event_base_id() const
{
    return hal::event::GAMEPAD_EVENTS;
}

int32_t right_button::get_event_id() const
{
    return event_id::right_button;
}

}
}
