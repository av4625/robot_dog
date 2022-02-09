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
        std::function<void(int8_t, int8_t)> event_callback) const = 0;
};

}
}

#endif
