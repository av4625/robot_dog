#ifndef CONTROLLER_HANDLERS_HPP
#define CONTROLLER_HANDLERS_HPP

#include <memory>

#include "context.hpp"

namespace controller
{

class handlers
{
public:
    virtual ~handlers(){}

    virtual void on_l_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) = 0;

    virtual void on_r_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) = 0;

    virtual void on_left_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_right_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_l1_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_r1_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_cross_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_circle_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void on_settings_button(const std::shared_ptr<context>& ctx) = 0;

    virtual void update(const std::shared_ptr<context>& ctx) = 0;
};

}

#endif
