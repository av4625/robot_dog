#ifndef CONTROLLER_STATE_LEAN_HPP
#define CONTROLLER_STATE_LEAN_HPP

#include "state_base.hpp"

namespace controller
{

class state_lean : public state_base
{
public:
    std::string get_name() const override;

    void on_entry(const std::shared_ptr<context>& ctx) override;

    void on_l_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) override;

    void on_r_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) override;

    void on_settings_button(const std::shared_ptr<context>& ctx) override;

    void update(const std::shared_ptr<context>& ctx) override;
};

}

#endif
