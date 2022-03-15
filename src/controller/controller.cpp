#include "controller.hpp"
#include "context_impl.hpp"
#include "handler_router.hpp"
#include "state_store_impl.hpp"

namespace controller
{

controller::controller(
    const std::shared_ptr<context>& ctx,
    const std::shared_ptr<handlers>& handlers) :
        ctx_(ctx),
        handlers_(handlers)
{
}

std::shared_ptr<controller> controller::create(
    const std::shared_ptr<robot::robot>& robot,
    const std::shared_ptr<hal::hardware::gamepad>& gamepad,
    const std::shared_ptr<hal::executer>& executer,
    const std::shared_ptr<hal::hardware::arduino>& arduino)
{
    return std::make_shared<controller>(
        std::make_shared<context_impl>(
            std::make_shared<state_store_impl>(),
            robot,
            gamepad,
            executer,
            arduino),
        std::make_shared<handler_router>());
}

void controller::on_l_stick_y_move(const int8_t y_location)
{
    handlers_->on_l_stick_y_move(ctx_, y_location);
}

void controller::on_r_stick_y_move(const int8_t y_location)
{
    handlers_->on_r_stick_y_move(ctx_, y_location);
}

void controller::on_l2_move(const uint8_t location)
{
    handlers_->on_l2_move(ctx_, location);
}

void controller::on_r2_move(const uint8_t location)
{
    handlers_->on_r2_move(ctx_, location);
}

void controller::on_left_button()
{
    handlers_->on_left_button(ctx_);
}

void controller::on_right_button()
{
    handlers_->on_right_button(ctx_);
}

void controller::on_l1_button()
{
    handlers_->on_l1_button(ctx_);
}

void controller::on_r1_button()
{
    handlers_->on_r1_button(ctx_);
}

void controller::on_cross_button()
{
    handlers_->on_cross_button(ctx_);
}

void controller::on_circle_button()
{
    handlers_->on_circle_button(ctx_);
}

void controller::on_settings_button()
{
    handlers_->on_settings_button(ctx_);
}

void controller::update()
{
    handlers_->update(ctx_);
}

}
