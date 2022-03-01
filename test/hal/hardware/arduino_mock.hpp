#ifndef HAL_HARDWARE_ARDUINO_MOCK_HPP
#define HAL_HARDWARE_ARDUINO_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/hardware/arduino.hpp>

namespace hal
{
namespace hardware
{

class arduino_mock : public arduino
{
public:
    MOCK_METHOD(
        void, begin, (unsigned long serial_baud_rate), (const, override));
    MOCK_METHOD(void, pin_mode, (uint8_t pin, uint8_t mode), (const, override));
    MOCK_METHOD(int, digital_read, (uint8_t pin), (const, override));
    MOCK_METHOD(uint16_t, analog_read, (uint8_t pin), (const, override));
    MOCK_METHOD(unsigned long, millis, (), (const, override));
    MOCK_METHOD(void, delay, (uint32_t milliseconds), (const, override));
    MOCK_METHOD(
        void, delay_microseconds, (uint32_t milliseconds), (const, override));
    MOCK_METHOD(void, print, (const char* message), (const, override));
    MOCK_METHOD(void, print, (int message), (const, override));
    MOCK_METHOD(void, print, (uint32_t message), (const, override));
    MOCK_METHOD(void, print, (double message), (const, override));
    MOCK_METHOD(void, println, (const char* message), (const, override));
    MOCK_METHOD(void, println, (int message), (const, override));
    MOCK_METHOD(void, println, (uint32_t message), (const, override));
    MOCK_METHOD(void, println, (double message), (const, override));
};

}
}

#endif
