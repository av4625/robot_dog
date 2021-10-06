#ifndef INPUT_DEVICES_ROTARY_ENCODER_HPP
#define INPUT_DEVICES_ROTARY_ENCODER_HPP

#include <memory>
#include "../hal/hardware/arduino.hpp"
#include "../hal/hardware/defines.hpp"
#include "rotary_encoder_states.hpp"

namespace input_devices
{

template <rotary_encoder_type e>
class rotary_encoder
{
public:
    rotary_encoder(
        uint8_t clock_pin,
        uint8_t data_pin,
        uint8_t switch_pin,
        const std::shared_ptr<hal::hardware::arduino>& arduino);

    virtual void begin();

    virtual rotation_direction check_rotary(const unsigned long& current_time);
    virtual button_press_type check_button(const unsigned long& current_time);

private:
    const uint8_t clock_pin_;
    const uint8_t data_pin_;
    const uint8_t switch_pin_;
    const int rotary_interval_;
    const int button_interval_;
    const std::shared_ptr<hal::hardware::arduino> arduino_;

    int previous_clock_;
    unsigned long previous_rotary_time_;
    int previous_button_state_;
    unsigned long previous_button_time_;
    unsigned long button_press_time_;
    bool change_detected_;
};

template<rotary_encoder_type e>
rotary_encoder<e>::rotary_encoder(
    const uint8_t clock_pin,
    const uint8_t data_pin,
    const uint8_t switch_pin,
    const std::shared_ptr<hal::hardware::arduino>& arduino)
    : clock_pin_(clock_pin),
      data_pin_(data_pin),
      switch_pin_(switch_pin),
      rotary_interval_(1),
      button_interval_(5),
      arduino_(arduino),
      previous_rotary_time_(0),
      previous_button_time_(0),
      button_press_time_(0),
      change_detected_(false)
{
}

template <rotary_encoder_type e>
void rotary_encoder<e>::begin()
{
    arduino_->pin_mode(clock_pin_, hal::hardware::input);
    arduino_->pin_mode(data_pin_, hal::hardware::input);
    arduino_->pin_mode(switch_pin_, hal::hardware::input_pullup);

    previous_clock_ = arduino_->digital_read(clock_pin_);
    previous_button_state_ = arduino_->digital_read(switch_pin_);
}

template <rotary_encoder_type e>
button_press_type rotary_encoder<e>::check_button(const unsigned long& current_time)
{
    if ((current_time - previous_button_time_) > button_interval_)
    {
        const int button_state = arduino_->digital_read(switch_pin_);

        if (button_state != previous_button_state_)
        {
            button_press_type return_state;
            // Button pressed down
            if (button_state == hal::hardware::low)
            {
                button_press_time_ = arduino_->millis();
                return_state = button_press_type::button_down;
            }
            // Button not pressed
            else
            {
                if ((current_time - button_press_time_) > 1500)
                {
                    arduino_->println("Long button press");
                    return_state = button_press_type::long_button_press;
                }
                else
                {
                    arduino_->println("Button press");
                    return_state = button_press_type::button_press;
                }
            }

            // save the current state as the last state, for next time through the loop
            previous_button_state_ = button_state;
            previous_button_time_ = arduino_->millis();

            return return_state;
        }
    }

    return button_press_type::no_button_press;
}

}

#endif
