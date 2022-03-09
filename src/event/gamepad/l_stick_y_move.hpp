#ifndef EVENT_GAMEPAD_L_STICK_Y_MOVE_HPP
#define EVENT_GAMEPAD_L_STICK_Y_MOVE_HPP

#include "../event.hpp"

namespace event
{
namespace gamepad
{

class l_stick_y_move : public event
{
public:
    explicit l_stick_y_move(int8_t data);

    const char* get_event_base_id() const override;

    int32_t get_event_id() const override;

    int8_t get_data() const;

private:
    const int8_t data_;
};

}
}

#endif
