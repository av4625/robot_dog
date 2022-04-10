#include "context_impl.hpp"

#include "../hal/hardware/arduino.hpp"
#include "../robot/robot.hpp"

#include "state_store.hpp"

namespace controller
{

context_impl::context_impl(
    const std::shared_ptr<state_store>& state_store,
    const std::shared_ptr<robot::robot>& robot,
    const std::shared_ptr<hal::hardware::gamepad>& gamepad,
    const std::shared_ptr<hal::executer>& executer,
    const std::shared_ptr<hal::hardware::arduino>& arduino) :
        state_store_(state_store),
        robot_(robot),
        gamepad_(gamepad),
        executer_(executer),
        arduino_(arduino),
        active_state_(state_store_->get_initial_state())
{
}

state& context_impl::get_state() const
{
    return *active_state_;
}

void context_impl::set_state(const state_id id)
{
    active_state_->on_exit(shared_from_this());
    active_state_ = state_store_->get_state(id);
    active_state_->on_entry(shared_from_this());
}

std::shared_ptr<robot::robot> context_impl::get_robot()
{
    return robot_;
}

void context_impl::set_gamepad_light_colour(
    const uint8_t r, const uint8_t g, const uint8_t b) const
{
    gamepad_->set_led(r, g, b);
    gamepad_->send();
}

void context_impl::small_rumble_controller(const short milliseconds) const
{
    /**
     * Pass shared_from_this to keep context_impl alive, pass this for ease of
     * using member data
     */
    const auto lifetime{shared_from_this()};
    executer_->execute([&milliseconds, lifetime, this] ()
    {
        gamepad_->set_rumble(255, 0);
        gamepad_->send();
        arduino_->delay(milliseconds);
        gamepad_->set_rumble(0, 0);
        gamepad_->send();
    });
}

void context_impl::large_rumble_controller(const short milliseconds) const
{
    /**
     * Pass shared_from_this to keep context_impl alive, pass this for ease of
     * using member data
     */
    const auto lifetime{shared_from_this()};
    executer_->execute([&milliseconds, lifetime, this] ()
    {
        gamepad_->set_rumble(0, 255);
        gamepad_->send();
        arduino_->delay(milliseconds);
        gamepad_->set_rumble(0, 0);
        gamepad_->send();
    });
}

}
