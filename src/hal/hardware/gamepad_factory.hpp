#ifndef HAL_HARDWARE_GAMEPAD_FACTORY_HPP
#define HAL_HARDWARE_GAMEPAD_FACTORY_HPP

#include <memory>

#include "../event_loop_fwd.hpp"
#include "../../utility/gamepad/events_fwd.hpp"

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
        const std::shared_ptr<event_loop>& event_loop) const = 0;
};

}
}

#endif
