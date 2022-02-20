#include "gamepad_factory_impl.hpp"
#include "ps4_controller.hpp"

namespace hal
{
namespace hardware
{

std::shared_ptr<gamepad> gamepad_factory_impl::create_ps4_gamepad(
    const std::string& mac_address,
    std::function<void()> connected_callback,
    std::function<void(utility::gamepad::events&&)> event_callback) const
{
    std::shared_ptr<ps4_controller> ps4_controller_instance{
        ps4_controller::instance_.lock()};

    if (!ps4_controller_instance)
    {
        ps4_controller_instance = std::make_shared<ps4_controller>(
            mac_address,
            std::move(connected_callback),
            std::move(event_callback));
        ps4_controller::instance_ = ps4_controller_instance;
    }

    return ps4_controller_instance;
}

}
}
