#ifndef HAL_HARDWARE_GAMEPAD_FACTORY_MOCK_HPP
#define HAL_HARDWARE_GAMEPAD_FACTORY_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/hardware/gamepad_factory.hpp>

namespace hal
{
namespace hardware
{

class gamepad_factory_mock : public gamepad_factory
{
public:
    MOCK_METHOD(
        std::shared_ptr<gamepad>,
        create_ps4_gamepad,
        (
            const std::string& mac_address,
            std::function<void()> connected_callback,
            std::function<void(
                std::pair<int8_t, bool>&&,
                std::pair<int8_t, bool>&&)> event_callback
        ),
        (const, override));
};

}
}

#endif
