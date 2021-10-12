#ifndef HAL_HARDWARE_SERVO_MOCK_HPP
#define HAL_HARDWARE_SERVO_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/hardware/servo.hpp>

namespace hal
{
namespace hardware
{

class servo_mock : public servo
{
public:
    MOCK_METHOD1(begin, void(uint8_t pin));
    MOCK_METHOD1(write_microseconds, void(short microseconds));
};

}
}

#endif
