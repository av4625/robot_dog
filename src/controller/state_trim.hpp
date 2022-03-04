#ifndef CONTROLLER_STATE_TRIM_HPP
#define CONTROLLER_STATE_TRIM_HPP

#include <cstdint>
#include <vector>

#include "../utility/robot/limb.hpp"

#include "state_base.hpp"

namespace controller
{

class state_trim : public state_base
{
public:
    state_trim();

    std::string get_name() const override;

    void on_entry(const std::shared_ptr<context>& ctx) override;

    void on_exit(const std::shared_ptr<context>& ctx) const override;

    void on_left_button(const std::shared_ptr<context>& ctx) override;

    void on_right_button(const std::shared_ptr<context>& ctx) override;

    void on_l1_button(const std::shared_ptr<context>& ctx) override;

    void on_r1_button(const std::shared_ptr<context>& ctx) override;

    void on_cross_button(const std::shared_ptr<context>& ctx) override;

    void on_circle_button(const std::shared_ptr<context>& ctx) override;

    void on_settings_button(const std::shared_ptr<context>& ctx) override;

private:
    const std::vector<utility::robot::limb> limbs_;
    const uint8_t number_of_limbs_;
    uint8_t active_limb_index_;
};

}

#endif
