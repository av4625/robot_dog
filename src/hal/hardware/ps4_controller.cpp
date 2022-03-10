#include "ps4_controller.hpp"

#include <PS4Controller.h>

#include "../../event/gamepad/circle_button.hpp"
#include "../../event/gamepad/cross_button.hpp"
#include "../../event/gamepad/l_stick_x_move.hpp"
#include "../../event/gamepad/l_stick_y_move.hpp"
#include "../../event/gamepad/l1_button.hpp"
#include "../../event/gamepad/l2_button.hpp"
#include "../../event/gamepad/left_button.hpp"
#include "../../event/gamepad/r_stick_x_move.hpp"
#include "../../event/gamepad/r_stick_y_move.hpp"
#include "../../event/gamepad/r1_button.hpp"
#include "../../event/gamepad/r2_button.hpp"
#include "../../event/gamepad/right_button.hpp"
#include "../../event/gamepad/settings_button.hpp"

// https://stackoverflow.com/questions/31018005/c-member-function-as-callback-function-to-external-library

namespace hal
{
namespace hardware
{

std::weak_ptr<ps4_controller> ps4_controller::instance_{};

ps4_controller::ps4_controller(
    const std::string& mac_address,
    std::function<void()> connected_callback,
    const std::shared_ptr<event_loop>& event_loop) :
        mac_address_(mac_address),
        connected_callback_(std::move(connected_callback)),
        event_loop_(event_loop),
        events_{
            {event::event_id::circle_button,
                std::make_shared<const event::gamepad::circle_button>()},
            {event::event_id::cross_button,
                std::make_shared<const event::gamepad::cross_button>()},
            {event::event_id::l_stick_x_move,
                std::make_shared<const event::gamepad::l_stick_x_move>()},
            {event::event_id::l_stick_y_move,
                std::make_shared<const event::gamepad::l_stick_y_move>()},
            {event::event_id::l1_button,
                std::make_shared<const event::gamepad::l1_button>()},
            {event::event_id::l2_button,
                std::make_shared<const event::gamepad::l2_button>()},
            {event::event_id::left_button,
                std::make_shared<const event::gamepad::left_button>()},
            {event::event_id::r_stick_x_move,
                std::make_shared<const event::gamepad::r_stick_x_move>()},
            {event::event_id::r_stick_y_move,
                std::make_shared<const event::gamepad::r_stick_y_move>()},
            {event::event_id::r1_button,
                std::make_shared<const event::gamepad::r1_button>()},
            {event::event_id::r2_button,
                std::make_shared<const event::gamepad::r2_button>()},
            {event::event_id::right_button,
                std::make_shared<const event::gamepad::right_button>()},
            {event::event_id::settings_button,
                std::make_shared<const event::gamepad::settings_button>()}}
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
        if(PS4.event.analog_move.stick.rx)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            int8_t rx{PS4.data.analog.stick.rx};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::r_stick_x_move),
                reinterpret_cast<void*>(&rx),
                sizeof(rx));
        }

        if(PS4.event.analog_move.stick.ry)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            int8_t ry{PS4.data.analog.stick.ry};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::r_stick_y_move),
                reinterpret_cast<void*>(&ry),
                sizeof(ry));
        }

        if(PS4.event.analog_move.stick.lx)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            int8_t lx{PS4.data.analog.stick.lx};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::l_stick_x_move),
                reinterpret_cast<void*>(&lx),
                sizeof(lx));
        }

        if(PS4.event.analog_move.stick.ly)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            int8_t ly{PS4.data.analog.stick.ly};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::l_stick_y_move),
                reinterpret_cast<void*>(&ly),
                sizeof(ly));
        }

        if (PS4.event.button_down.left)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::left_button));
        }

        if (PS4.event.button_down.right)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::right_button));
        }

        if (PS4.event.button_down.l1)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::l1_button));
        }

        if (PS4.event.analog_move.button.l2)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            uint8_t l2{PS4.data.analog.button.l2};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::l2_button),
                reinterpret_cast<void*>(&l2),
                sizeof(l2));
        }

        if (PS4.event.button_down.r1)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::r1_button));
        }

        if (PS4.event.analog_move.button.r2)
        {
            // Event loop takes a deep copy of this data, so it is ok to send a
            // pointer to it
            uint8_t r2{PS4.data.analog.button.r2};
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::r2_button),
                reinterpret_cast<void*>(&r2),
                sizeof(r2));
        }

        if (PS4.event.button_down.cross)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::cross_button));
        }

        if (PS4.event.button_down.circle)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::circle_button));
        }

        if (PS4.event.button_down.options)
        {
            instance->event_loop_->send_event(
                instance->events_.at(event::event_id::settings_button));
        }
    }
}

}
}
