#ifndef INPUT_DEVICES_POTENTIOMETER_HPP
#define INPUT_DEVICES_POTENTIOMETER_HPP

#include <cstdint>
#include <memory>
#include "../hal/hardware/arduino.hpp"

namespace input_devices
{

class potentiometer
{
public:
    potentiometer(
        const std::shared_ptr<hal::hardware::arduino>& arduino, uint8_t pin);
    virtual ~potentiometer(){}
    virtual uint16_t read() const;

private:
    const std::shared_ptr<hal::hardware::arduino> arduino_;
    const uint8_t pin_;

};

}

#endif
