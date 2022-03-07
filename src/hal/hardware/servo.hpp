#ifndef HAL_HARDWARE_SERVO_HPP
#define HAL_HARDWARE_SERVO_HPP

#include <cstdint>
#include <utility>

namespace hal
{
namespace hardware
{

class servo
{
public:
    virtual ~servo(){}

    virtual void begin() = 0;

    virtual void write_microseconds(short microseconds) = 0;

    /**
     * @brief Return the minimum amount of time for the servo to do 180 degrees
     *        in milliseconds.
     *
     * @return time in milliseconds.
     */
    virtual short get_minimum_time_for_180() const = 0;

    /**
     * @brief Return 0 degrees and 180 degrees in microseconds.
     *
     * @return pair containing microsecond values for 0 degrees (first) and 180
     *         degrees (second).
     */
    virtual const std::pair<short, short>& get_microsecond_values() const = 0;
};

}
}

#endif
