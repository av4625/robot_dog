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
    MOCK_CONST_METHOD1(begin, void(unsigned long serial_baud_rate));
    MOCK_CONST_METHOD2(pin_mode, void(uint8_t pin, uint8_t mode));
    MOCK_CONST_METHOD1(digital_read, int(uint8_t pin));
    MOCK_CONST_METHOD1(analog_read, uint16_t(uint8_t pin));
    MOCK_CONST_METHOD0(millis, unsigned long());
    MOCK_CONST_METHOD1(print, void(const char* message));
    MOCK_CONST_METHOD1(print, void(int message));
    MOCK_CONST_METHOD1(print, void(double message));
    MOCK_CONST_METHOD1(println, void(const char* message));
    MOCK_CONST_METHOD1(println, void(int message));
    MOCK_CONST_METHOD1(println, void(double message));
};

}
}

#endif
