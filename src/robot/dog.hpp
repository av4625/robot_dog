#ifndef ROBOT_DOG_HPP
#define ROBOT_DOG_HPP

#include "robot.hpp"

#include <memory>

#include "../hal/config/manager_fwd.hpp"
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
        std::unique_ptr<hal::config::manager> config);

    void begin() override;

    void set_position(int8_t height, int8_t forward_back) override;

    void set_height(int8_t height) override;

    void set_forward_back(int8_t forward_back) override;

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

    utility::config::robot_settings dog_settings_;
};

}

#endif
