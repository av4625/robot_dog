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
    explicit servo_impl(uint8_t pin);

    servo_impl(
        short minimum_time_for_max_rotation,
        short min_microseconds,
        short max_microseconds,
        uint8_t pin);

    void begin() override;

    void write_microseconds(short microseconds) override;

    short get_minimum_time_for_180() const override;

    const std::pair<short, short>& get_microsecond_values() const override;

private:
    Servo servo_;
    const short minimum_time_for_max_rotation_;
    const std::pair<short, short> microseconds_range_;
    const uint8_t pin_;
};

}
}

#endif
