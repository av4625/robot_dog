#include "handler_router.hpp"
#include "state.hpp"

namespace controller
{

void handler_router::on_l_stick_x_move(
    const std::shared_ptr<context>& ctx,
    const int8_t x_location)
{
    ctx->get_state().on_l_stick_x_move(ctx, x_location);
}

void handler_router::on_l_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
    ctx->get_state().on_l_stick_y_move(ctx, y_location);
}

void handler_router::on_r_stick_x_move(
    const std::shared_ptr<context>& ctx,
    const int8_t x_location)
{
    ctx->get_state().on_r_stick_x_move(ctx, x_location);
}

void handler_router::on_r_stick_y_move(
    const std::shared_ptr<context>& ctx,
    const int8_t y_location)
{
    ctx->get_state().on_r_stick_y_move(ctx, y_location);
}

void handler_router::on_l2_move(
    const std::shared_ptr<context>& ctx,
    const uint8_t location)
{
    ctx->get_state().on_l2_move(ctx, location);
}

void handler_router::on_r2_move(
    const std::shared_ptr<context>& ctx,
    const uint8_t location)
{
    ctx->get_state().on_r2_move(ctx, location);
}

void handler_router::on_left_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_left_button(ctx);
}

void handler_router::on_right_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_right_button(ctx);
}

void handler_router::on_l1_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_l1_button(ctx);
}

void handler_router::on_r1_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_r1_button(ctx);
}

void handler_router::on_cross_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_cross_button(ctx);
}

void handler_router::on_circle_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_circle_button(ctx);
}

void handler_router::on_settings_button(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().on_settings_button(ctx);
}

void handler_router::update(const std::shared_ptr<context>& ctx)
{
    ctx->get_state().update(ctx);
}

}
