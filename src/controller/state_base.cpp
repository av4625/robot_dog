#include "state_base.hpp"

namespace controller
{

void state_base::on_entry(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_exit(const std::shared_ptr<context>& ctx) const
{
}

void state_base::on_l_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
}

void state_base::on_r_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
}

void state_base::on_left_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_right_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_l1_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_r1_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_cross_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_circle_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::on_settings_button(const std::shared_ptr<context>& ctx)
{
}

void state_base::update(const std::shared_ptr<context>& ctx)
{
}

}
