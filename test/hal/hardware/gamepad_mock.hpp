#ifndef HAL_HARDWARE_GAMEPAD_MOCK_HPP
#define HAL_HARDWARE_GAMEPAD_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/hardware/gamepad.hpp>

namespace hal
{
namespace hardware
{

class gamepad_mock : public gamepad
{
public:
    MOCK_METHOD(void, begin, (), (const, override));

    MOCK_METHOD(
        void, set_rumble, (uint8_t small, uint8_t large), (const, override));

    MOCK_METHOD(
        void, set_led, (uint8_t r, uint8_t g, uint8_t b), (const, override));

    MOCK_METHOD(void, send, (), (const, override));
};

}
}

#endif
