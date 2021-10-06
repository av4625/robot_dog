#ifndef HAL_HARDWARE_ARDUINO_HPP
#define HAL_HARDWARE_ARDUINO_HPP

#include "defines.hpp"

namespace hal
{
namespace hardware
{

class arduino
{
public:
    virtual ~arduino(){}
    virtual void begin(unsigned long serial_baud_rate) const = 0;
    virtual void pin_mode(uint8_t pin, uint8_t mode) const = 0;
    virtual int digital_read(uint8_t pin) const = 0;
    virtual uint16_t analog_read(uint8_t pin) const = 0;
    virtual unsigned long millis() const = 0;
    virtual void print(const char* message) const = 0;
    virtual void print(int message) const = 0;
    virtual void print(double message) const = 0;
    virtual void println(const char* message) const = 0;
    virtual void println(int message) const = 0;
    virtual void println(double message) const = 0;
};

}
}

#endif
