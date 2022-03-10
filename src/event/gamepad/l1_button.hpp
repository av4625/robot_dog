#ifndef EVENT_GAMEPAD_L1_BUTTON_HPP
#define EVENT_GAMEPAD_L1_BUTTON_HPP

#include "../event.hpp"

namespace event
{
namespace gamepad
{

class l1_button : public event
{
public:
    const char* get_event_base_id() const override;

    int32_t get_event_id() const override;
};

}
}

#endif
