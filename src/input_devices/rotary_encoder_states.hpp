#ifndef INPUT_DEVICES_ROTARY_ENCODER_STATES_HPP
#define INPUT_DEVICES_ROTARY_ENCODER_STATES_HPP

namespace input_devices
{

enum class rotary_encoder_type
{
    ec11,
    ky040
};

enum class rotation_direction
{
    left,
    right,
    no_rotation
};

enum class button_press_type
{
    button_down,
    button_press,
    long_button_press,
    no_button_press
};

}

#endif
