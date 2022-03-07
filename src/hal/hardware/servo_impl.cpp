#include "servo_impl.hpp"

namespace hal
{
namespace hardware
{

servo_impl::servo_impl(const uint8_t pin) :
    minimum_time_for_max_rotation_(500),
    microseconds_range_(std::make_pair(500, 2500)),
    pin_(pin)
{
}

servo_impl::servo_impl(
    const short minimum_time_for_max_rotation,
    const short min_microseconds,
    const short max_microseconds,
    const uint8_t pin) :
        minimum_time_for_max_rotation_(minimum_time_for_max_rotation),
        microseconds_range_(std::make_pair(min_microseconds, max_microseconds)),
        pin_(pin)
{
}

void servo_impl::begin()
{
    servo_.setPeriodHertz(50);
    servo_.attach(pin_, microseconds_range_.first, microseconds_range_.second);
}

void servo_impl::write_microseconds(const short microseconds)
{
    servo_.writeMicroseconds(microseconds);
}

short servo_impl::get_minimum_time_for_180() const
{
    return minimum_time_for_max_rotation_;
}

const std::pair<short, short>& servo_impl::get_microsecond_values() const
{
    return microseconds_range_;
}

}
}
