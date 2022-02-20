#ifndef HAL_HARDWARE_GAMEPAD_FACTORY_IMPL_HPP
#define HAL_HARDWARE_GAMEPAD_FACTORY_IMPL_HPP

#include "gamepad_factory.hpp"

namespace hal
{
namespace hardware
{

class gamepad_factory_impl : public gamepad_factory
{
public:
    std::shared_ptr<gamepad> create_ps4_gamepad(
        const std::string& mac_address,
        std::function<void()> connected_callback,
        std::function<
            void(utility::gamepad::events&&)> event_callback) const override;
};

}
}

#endif
