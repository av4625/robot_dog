#include "gamepad_factory_impl.hpp"
#include "ps4_controller.hpp"

namespace hal
{
namespace hardware
{

std::shared_ptr<gamepad> gamepad_factory_impl::create_ps4_gamepad(
    const std::string& mac_address,
    std::function<void()> connected_callback,
    const std::shared_ptr<event_loop>& event_loop) const
{
    std::shared_ptr<ps4_controller> ps4_controller_instance{
        ps4_controller::instance_.lock()};

    if (!ps4_controller_instance)
    {
        ps4_controller_instance = std::make_shared<ps4_controller>(
            mac_address,
            std::move(connected_callback),
            event_loop);
        ps4_controller::instance_ = ps4_controller_instance;
    }

    return ps4_controller_instance;
}

}
}
