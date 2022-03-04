#ifndef CONTROLLER_CONTEXT_IMPL_HPP
#define CONTROLLER_CONTEXT_IMPL_HPP

#include "context.hpp"

#include "../hal/executer.hpp"
#include "../hal/hardware/arduino_fwd.hpp"
#include "../hal/hardware/gamepad.hpp"

#include "state_store_fwd.hpp"

namespace controller
{

class context_impl :
    public context,
    public std::enable_shared_from_this<context_impl>
{
public:
    context_impl(
        const std::shared_ptr<state_store>& state_store,
        const std::shared_ptr<robot::robot>& robot,
        const std::shared_ptr<hal::hardware::gamepad>& gamepad,
        const std::shared_ptr<hal::executer>& executer,
        const std::shared_ptr<hal::hardware::arduino>& arduino);

    state& get_state() const override;

    void set_state(state_id id) override;

    std::shared_ptr<robot::robot> get_robot() override;

    void set_gamepad_light_colour(
        uint8_t r, uint8_t g, uint8_t b) const override;

    void small_rumble_controller(short milliseconds) const override;

    void large_rumble_controller(short milliseconds) const override;

private:
    const std::shared_ptr<state_store> state_store_;
    const std::shared_ptr<robot::robot> robot_;
    const std::shared_ptr<hal::hardware::gamepad> gamepad_;
    const std::shared_ptr<hal::executer> executer_;
    const std::shared_ptr<hal::hardware::arduino> arduino_;
    state* active_state_;
};

}

#endif
