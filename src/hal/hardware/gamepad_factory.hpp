#ifndef HAL_HARDWARE_GAMEPAD_FACTORY_HPP
#define HAL_HARDWARE_GAMEPAD_FACTORY_HPP

#include <memory>

#include "gamepad.hpp"

namespace hal
{
namespace hardware
{

class gamepad_factory
{
public:
    virtual ~gamepad_factory(){}

    virtual std::shared_ptr<gamepad> create_ps4_gamepad(
        const std::string& mac_address,
        std::function<void()> connected_callback,
        std::function<void(
            std::pair<int8_t, bool>&&,
            std::pair<int8_t, bool>&&)> event_callback) const = 0;
};

}
}

#endif
