#include "state_lean.hpp"

#include "../robot/robot.hpp"

namespace controller
{

std::string state_lean::get_name() const
{
    static std::string name("lean");
    return name;
}

void state_lean::on_entry(const std::shared_ptr<context>& ctx)
{
    ctx->large_rumble_controller(1000);
    ctx->set_gamepad_light_colour(0, 0, 255);
}

void state_lean::on_l_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
    ctx->get_robot()->set_height(y_location);
}

void state_lean::on_r_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
    ctx->get_robot()->set_forward_back(y_location);
}

void state_lean::on_settings_button(const std::shared_ptr<context>& ctx)
{
    ctx->set_state(state_id::trim);
}

void state_lean::update(const std::shared_ptr<context>& ctx)
{
    // Check if I need to update, by saving previous update return (is it worth
    // it do to this?)
    ctx->get_robot()->update_position();
}

}
