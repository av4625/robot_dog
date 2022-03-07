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
    MOCK_METHOD(void, begin, (), (override));
    MOCK_METHOD(void, write_microseconds, (short microseconds), (override));
    MOCK_METHOD(short, get_minimum_time_for_180, (), (const, override));
    MOCK_METHOD(
        (const std::pair<short, short>&),
        get_microsecond_values,
        (),
        (const, override));
};

}
}

#endif
