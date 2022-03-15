#ifndef CONTROLLER_CONTROLLER_HPP
#define CONTROLLER_CONTROLLER_HPP

#include <memory>

#include "../hal/executer_fwd.hpp"
#include "../hal/hardware/arduino_fwd.hpp"
#include "../hal/hardware/gamepad_fwd.hpp"
#include "../robot/robot_fwd.hpp"

#include "context.hpp"
#include "handlers.hpp"

namespace controller
{

class controller
{
public:
    virtual ~controller(){}

    controller(
        const std::shared_ptr<context>& ctx,
        const std::shared_ptr<handlers>& handlers);

    static std::shared_ptr<controller> create(
        const std::shared_ptr<robot::robot>& robot,
        const std::shared_ptr<hal::hardware::gamepad>& gamepad,
        const std::shared_ptr<hal::executer>& executer,
        const std::shared_ptr<hal::hardware::arduino>& arduino);

    void on_l_stick_y_move(int8_t y_location);

    void on_r_stick_y_move(int8_t y_location);

    void on_l2_move(uint8_t location);

    void on_r2_move(uint8_t location);

    void on_left_button();

    void on_right_button();

    void on_l1_button();

    void on_r1_button();

    void on_cross_button();

    void on_circle_button();

    void on_settings_button();

    void update();

private:
    const std::shared_ptr<context> ctx_;
    const std::shared_ptr<handlers> handlers_;
};

}

#endif
