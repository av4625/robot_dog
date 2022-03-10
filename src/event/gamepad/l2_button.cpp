#include "l2_button.hpp"

#include "../event_id.hpp"
#include "../../hal/event/event_base_id.hpp"

namespace event
{
namespace gamepad
{

const char* l2_button::get_event_base_id() const
{
    return hal::event::GAMEPAD_EVENTS;
}

int32_t l2_button::get_event_id() const
{
    return event_id::l2_button;
}

}
}
