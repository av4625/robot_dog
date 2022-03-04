#ifndef CONTROLLER_CONTEXT_MOCK_HPP
#define CONTROLLER_CONTEXT_MOCK_HPP

#include <gmock/gmock.h>
#include <controller/context.hpp>

namespace controller
{

class context_mock : public context
{
public:
    MOCK_METHOD(state&, get_state, (), (const, override));

    MOCK_METHOD(void, set_state, (state_id id), (override));

    MOCK_METHOD(std::shared_ptr<robot::robot>, get_robot, (), (override));

    MOCK_METHOD(
        void,
        set_gamepad_light_colour,
        (uint8_t r, uint8_t g, uint8_t b),
        (const, override));

    MOCK_METHOD(
        void,
        small_rumble_controller,
        (short milliseconds),
        (const, override));

    MOCK_METHOD(
        void,
        large_rumble_controller,
        (short milliseconds),
        (const, override));
};

}

#endif
