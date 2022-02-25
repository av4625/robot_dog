#include "ps4_controller.hpp"
#include <PS4Controller.h>
#include "../../utility/gamepad/events.hpp"

// https://stackoverflow.com/questions/31018005/c-member-function-as-callback-function-to-external-library

namespace hal
{
namespace hardware
{

std::weak_ptr<ps4_controller> ps4_controller::instance_{};

ps4_controller::ps4_controller(
    const std::string& mac_address,
    std::function<void()> connected_callback,
    std::function<void(utility::gamepad::events&&)> event_callback) :
        mac_address_(mac_address),
        connected_callback_(std::move(connected_callback)),
        event_callback_(std::move(event_callback))
{
}

void ps4_controller::begin() const
{
    PS4.attachOnConnect(connected_callback);
    PS4.attach(event_callback);
    PS4.begin(mac_address_.c_str());
}

void ps4_controller::set_rumble(const uint8_t small, const uint8_t large) const
{
    PS4.setRumble(small, large);
}

void ps4_controller::set_led(
    const uint8_t r, const uint8_t g, const uint8_t b) const
{
    PS4.setLed(r, g, b);
}

void ps4_controller::send() const
{
    PS4.sendToController();
}

void ps4_controller::connected_callback()
{
    const std::shared_ptr<ps4_controller> instance{instance_.lock()};

    if (instance)
    {
        instance->connected_callback_();
    }
}

void ps4_controller::event_callback()
{
    const std::shared_ptr<ps4_controller> instance{instance_.lock()};

    if (instance)
    {
        utility::gamepad::events events;

        if(PS4.event.analog_move.stick.ry)
        {
            events.r_stick_y = std::make_pair(PS4.data.analog.stick.ry, true);
        }
        else
        {
            events.r_stick_y = std::make_pair(0, false);
        }

        if(PS4.event.analog_move.stick.ly)
        {
            events.l_stick_y = std::make_pair(PS4.data.analog.stick.ly, true);
        }
        else
        {
            events.l_stick_y = std::make_pair(0, false);
        }

        events.settings = PS4.event.button_down.left;
        events.settings = PS4.event.button_down.right;
        events.settings = PS4.event.button_down.l1;
        events.settings = PS4.event.button_down.r1;
        events.cross = PS4.event.button_down.cross;
        events.circle = PS4.event.button_down.circle;
        events.settings = PS4.event.button_down.options;

        instance->event_callback_(std::move(events));
    }
}

}
}
