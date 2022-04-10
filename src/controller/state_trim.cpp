#include "state_trim.hpp"

#include "../robot/robot.hpp"

namespace controller
{

state_trim::state_trim() :
    limbs_({
        utility::robot::limb::front_left,
        utility::robot::limb::rear_left,
        utility::robot::limb::front_right,
        utility::robot::limb::rear_right}),
    number_of_limbs_(limbs_.size()),
    active_limb_index_(0)
{
}

std::string state_trim::get_name() const
{
    static std::string name("trim");
    return name;
}

void state_trim::on_entry(const std::shared_ptr<context>& ctx)
{
    ctx->large_rumble_controller(1000);
    ctx->set_gamepad_light_colour(255, 0, 0);
    active_limb_index_ = 0;

    const auto robot(ctx->get_robot());

    robot->fully_extend_legs();
    /**
     * Should I continually call `update` in an executer here so that the legs
     * get extended. The executer will execute on the same core but at a higher
     * priority so will effectively block the `controller` until the legs are
     * extended, which is what I want. Or should I just keep calling update here
     * and block until its completed?
     */
    while(!robot->update_position())
    {
    }
}

void state_trim::on_exit(const std::shared_ptr<context>& ctx) const
{
    const auto robot(ctx->get_robot());
    robot->set_legs_in_neutral_position();
    /**
     * Should I continually call `update` in an executer here so that the legs
     * get set to a neutral position. The executer will execute on the same core
     * but at a higher priority so will effectively block the `controller` until
     * the legs are set in a neutral position, which is what I want. Or should I
     * just keep calling update here and block until its completed?
     */
    while(!robot->update_position())
    {
    }
}

void state_trim::on_left_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_robot()->trim_joint(
        limbs_[active_limb_index_],
        utility::robot::joint::knee,
        utility::robot::direction::anti_clockwise);
}

void state_trim::on_right_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_robot()->trim_joint(
        limbs_[active_limb_index_],
        utility::robot::joint::knee,
        utility::robot::direction::clockwise);
}

void state_trim::on_l1_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_robot()->trim_joint(
        limbs_[active_limb_index_],
        utility::robot::joint::shoulder,
        utility::robot::direction::clockwise);
}

void state_trim::on_r1_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_robot()->trim_joint(
        limbs_[active_limb_index_],
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise);
}

void state_trim::on_cross_button(const std::shared_ptr<context>& ctx)
{
    ctx->small_rumble_controller(250);
    active_limb_index_ = (active_limb_index_ + 1) % number_of_limbs_;
}

void state_trim::on_circle_button(const std::shared_ptr<context>& ctx)
{
    ctx->set_state(state_id::lean);
}

void state_trim::on_settings_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_robot()->save_trim_values();
    ctx->set_state(state_id::lean);
}

}
