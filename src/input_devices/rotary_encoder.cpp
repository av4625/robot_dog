#include "rotary_encoder.hpp"

namespace input_devices
{

template<>
rotation_direction rotary_encoder<rotary_encoder_type::ky040>::check_rotary(
    const unsigned long& current_time)
{
    if ((current_time - previous_rotary_time_) > rotary_interval_)
    {
        const int current_clock = arduino_->digital_read(clock_pin_);

        // No change or bounce
        if (current_clock == previous_clock_)
        {
            return rotation_direction::no_rotation;
        }

        const int current_data = arduino_->digital_read(data_pin_);
        rotation_direction return_direction;

        if (current_clock ^ current_data)
        {
            // Clockwise
            arduino_->println("Rotation Direction: right");
            return_direction = rotation_direction::right;
        }
        else
        {
            // Counterclockwise
            arduino_->println("Rotation Direction: left");
            return_direction = rotation_direction::left;
        }

        previous_clock_ = current_clock;
        previous_rotary_time_ = arduino_->millis();

        return return_direction;
    }

    return rotation_direction::no_rotation;
}

template<>
rotation_direction rotary_encoder<rotary_encoder_type::ec11>::check_rotary(
    const unsigned long& current_time)
{
    const int current_clock = arduino_->digital_read(clock_pin_);

    // If a change has been detected and enough time for a bounce has passed
    if (change_detected_ && (current_time - previous_rotary_time_) > rotary_interval_)
    {
        // Processes the change, set to false so we can wait for the next change
        change_detected_ = false;

        // We are between rotations, set previous clock so we know direction
        // when the rotation completes
        if (current_clock == 0)
        {
            previous_clock_ = current_clock;
            return rotation_direction::no_rotation;
        }

        const int current_data = arduino_->digital_read(data_pin_);
        rotation_direction return_direction;

        if (current_clock ^ current_data)
        {
            // Clockwise
            arduino_->println("Rotation Direction: right");
            return_direction = rotation_direction::right;
        }
        else
        {
            // Counterclockwise
            arduino_->println("Rotation Direction: left");
            return_direction = rotation_direction::left;
        }

        previous_clock_ = current_clock;
        previous_rotary_time_ = arduino_->millis();

        return return_direction;
    }
    // If we have processed the last change lets check for another
    else if (!change_detected_)
    {
        // No change
        if (current_clock == previous_clock_)
        {
            change_detected_ = false;
        }
        // There was a change
        else
        {
            change_detected_ = true;
        }

        // Don't set previous clock incase this was a bounce, wait for the
        // wait for the interval then set it

        previous_rotary_time_ = arduino_->millis();

    }

    return rotation_direction::no_rotation;
}

}
