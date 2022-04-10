#ifndef ROBOT_DOG_HPP
#define ROBOT_DOG_HPP

#include "robot.hpp"

#include <memory>

#include "../hal/config/manager_fwd.hpp"
#include "../mathmatics/calculations.hpp"
#include "../utility/config/robot_settings.hpp"

#include "leg_fwd.hpp"

namespace robot
{

class dog : public robot
{
public:
    dog(
        std::unique_ptr<leg> front_left,
        std::unique_ptr<leg> rear_left,
        std::unique_ptr<leg> front_right,
        std::unique_ptr<leg> rear_right,
        std::unique_ptr<hal::config::manager> config,
        const std::shared_ptr<const mathmatics::calculations>& calc);

    void begin() override;

    void set_position(
        int8_t height,
        int8_t forward_back,
        int8_t forward_back_lean,
        int8_t side_to_side_lean) override;

    void set_height(int8_t height) override;

    void set_forward_back(int8_t forward_back) override;

    void set_forward_back_lean(int8_t lean) override;

    void set_side_to_side_lean(int8_t lean) override;

    bool update_position() override;

    void fully_extend_legs() override;

    void set_legs_in_neutral_position() override;

    void trim_joint(
        utility::robot::limb limb,
        utility::robot::joint joint,
        utility::robot::direction direction) override;

    void save_trim_values() override;

private:
    const std::unique_ptr<leg> front_left_;
    const std::unique_ptr<leg> rear_left_;
    const std::unique_ptr<leg> front_right_;
    const std::unique_ptr<leg> rear_right_;
    const std::unique_ptr<hal::config::manager> config_;
    const std::shared_ptr<const mathmatics::calculations> calc_;

    utility::config::robot_settings dog_settings_;
    int8_t previous_height_;
    int8_t previous_forward_back_lean_;
    int8_t previous_side_to_side_lean_;

    int8_t calculate_leg_height(
        utility::robot::limb limb,
        int8_t height,
        int8_t forward_back_lean,
        int8_t side_to_side_lean) const;
};

}

#endif
