#ifndef HAL_HARDWARE_PS4_CONTROLLER_HPP
#define HAL_HARDWARE_PS4_CONTROLLER_HPP

#include "gamepad.hpp"

#include <memory>
#include <utility>

#include "../../utility/gamepad/events_fwd.hpp"

#include "gamepad_factory_impl.hpp"

namespace hal
{
namespace hardware
{

class ps4_controller : public gamepad
{
public:
    ps4_controller(
        const std::string& mac_address,
        std::function<void()> connected_callback,
        std::function<void(utility::gamepad::events&&)> event_callback);

    void begin() const override;

    void set_rumble(uint8_t small, uint8_t large) const override;

    void set_led(uint8_t r, uint8_t g, uint8_t b) const override;

    void send() const override;

private:
    friend class gamepad_factory_impl;

    static void connected_callback();
    static void event_callback();

    /**
     * This class will be a singleton. The instance will be stored in this weak
     * pointer. This has to be done so that a private static method can be used
     * as a callback to the 3rd party function as the third party function
     * doesn't allow the user to pass any data (like an instance) through to the
     * callback.
     */
    static std::weak_ptr<ps4_controller> instance_;

    const std::string mac_address_;
    const std::function<void()> connected_callback_;
    const std::function<void(utility::gamepad::events&&)> event_callback_;
};

}
}

#endif
