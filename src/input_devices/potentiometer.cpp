#include "potentiometer.hpp"

namespace input_devices
{

potentiometer::potentiometer(
    const std::shared_ptr<hal::hardware::arduino>& arduino,
    const uint8_t pin) :
        arduino_(arduino),
        pin_(pin)
{
}

uint16_t potentiometer::read() const
{
    return arduino_->analog_read(pin_);
}

}
