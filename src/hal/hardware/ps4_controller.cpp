#include "ps4_controller.hpp"
#include <PS4Controller.h>

// https://stackoverflow.com/questions/31018005/c-member-function-as-callback-function-to-external-library

namespace hal
{
namespace hardware
{

std::weak_ptr<ps4_controller> ps4_controller::instance_{};

ps4_controller::ps4_controller(
    const std::string& mac_address,
    std::function<void()> connected_callback,
    std::function<void(
        std::pair<int8_t, bool>&&,
        std::pair<int8_t, bool>&&)> event_callback) :
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
        std::pair<int8_t, bool> forward_back;
        std::pair<int8_t, bool> height;

        if(PS4.event.analog_move.stick.rx)
        {
            forward_back = std::make_pair(PS4.data.analog.stick.rx, true);
        }
        else
        {
            forward_back = std::make_pair(0, false);
        }

        if(PS4.event.analog_move.stick.ly)
        {
            height = std::make_pair(PS4.data.analog.stick.ly, true);
        }
        else
        {
            height = std::make_pair(0, false);
        }

        instance->event_callback_(std::move(forward_back), std::move(height));
    }
}

}
}
