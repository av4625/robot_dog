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
    std::function<void(int8_t, int8_t)> event_callback) :
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
        int8_t forward_back;
        int8_t height;

        if(PS4.event.analog_move.stick.rx)
        {
            forward_back = PS4.data.analog.stick.rx;
        }

        if(PS4.event.analog_move.stick.ly)
        {
            height = PS4.data.analog.stick.ly;
        }

        instance->event_callback_(forward_back, height);
    }
}

}
}
