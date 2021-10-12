#ifndef HAL_HARDWARE_SERVO_IMPL_HPP
#define HAL_HARDWARE_SERVO_IMPL_HPP

#include "servo.hpp"
#include <ESP32Servo.h>

namespace hal
{
namespace hardware
{

class servo_impl : public servo
{
public:
    servo_impl();

    servo_impl(
        short minimum_time_for_max_rotation,
        short min_microseconds,
        short max_microseconds);

    void begin(uint8_t pin);

    void write_microseconds(short microseconds);

    short get_minimum_time_for_180() const;

    const std::pair<short, short>& get_microsecond_values() const;

private:
    Servo servo_;
    const short minimum_time_for_max_rotation_;
    const std::pair<short, short> microseconds_range_;
};

}
}

#endif
