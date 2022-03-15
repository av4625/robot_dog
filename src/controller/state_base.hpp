#ifndef CONTROLLER_STATE_BASE_HPP
#define CONTROLLER_STATE_BASE_HPP

#include "state.hpp"

namespace controller
{

class state_base : public state
{
public:
    void on_entry(const std::shared_ptr<context>& ctx) override;

    void on_exit(const std::shared_ptr<context>& ctx) const override;

    void on_l_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) override;

    void on_r_stick_y_move(
        const std::shared_ptr<context>& ctx,
        int8_t y_location) override;

    void on_l2_move(
        const std::shared_ptr<context>& ctx,
        uint8_t location) override;

    void on_r2_move(
        const std::shared_ptr<context>& ctx,
        uint8_t location) override;

    void on_left_button(const std::shared_ptr<context>& ctx) override;

    void on_right_button(const std::shared_ptr<context>& ctx) override;

    void on_l1_button(const std::shared_ptr<context>& ctx) override;

    void on_r1_button(const std::shared_ptr<context>& ctx) override;

    void on_cross_button(const std::shared_ptr<context>& ctx) override;

    void on_circle_button(const std::shared_ptr<context>& ctx) override;

    void on_settings_button(const std::shared_ptr<context>& ctx) override;

    void update(const std::shared_ptr<context>& ctx) override;
};

}

#endif
