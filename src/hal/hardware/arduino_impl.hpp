#ifndef HAL_HARDWARE_ARDUINO_IMPL_HPP
#define HAL_HARDWARE_ARDUINO_IMPL_HPP

#include "arduino.hpp"

namespace hal
{
namespace hardware
{

class arduino_impl : public arduino
{
public:
    void begin(unsigned long serial_baud_rate) const override;
    void pin_mode(uint8_t pin, uint8_t mode) const override;
    int digital_read(uint8_t pin) const override;
    uint16_t analog_read(uint8_t pin) const override;
    unsigned long millis() const override;
    void delay(uint32_t milliseconds) const override;
    void delay_microseconds(uint32_t milliseconds) const override;
    void print(const char* message) const override;
    void print(int message) const override;
    void print(uint32_t message) const override;
    void print(double message) const override;
    void println(const char* message) const override;
    void println(int message) const override;
    void println(uint32_t message) const override;
    void println(double message) const override;
};

}
}

#endif
