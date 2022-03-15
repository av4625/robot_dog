#include <memory>
#include <utility>

#include "src/controller/controller.hpp"
#include "src/hal/core_executer.hpp"
#include "src/hal/config/manager_impl.hpp"
#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/gamepad_factory_impl.hpp"
#include "src/hal/robot/leg_factory_impl.hpp"
#include "src/mathmatics/calculations_impl.hpp"
#include "src/robot/dog.hpp"
#include "src/utility/gamepad/atomic_events.hpp"
#include "src/utility/gamepad/events.hpp"

void ps4_controller_connected();
void ps4_controller_event(utility::gamepad::events&& events);

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};

const std::shared_ptr<hal::hardware::gamepad_factory> gamepad_factory{
    std::make_shared<hal::hardware::gamepad_factory_impl>()};
const std::shared_ptr<hal::hardware::gamepad> gamepad{
    gamepad_factory->create_ps4_gamepad(
        "11:11:11:11:11:11",
        &ps4_controller_connected,
        &ps4_controller_event)};

const std::shared_ptr<hal::executer> executer{
    std::make_shared<hal::core_executer>()};

const std::shared_ptr<const mathmatics::calculations> calculations{
    std::make_shared<const mathmatics::calculations_impl>()};

const std::unique_ptr<hal::robot::leg_factory> leg_factory{
    new hal::robot::leg_factory_impl()};

std::unique_ptr<hal::config::manager> config_manager{
    new hal::config::manager_impl()};

const std::shared_ptr<robot::robot> dog{
    std::make_shared<robot::dog>(
        leg_factory->create(
            utility::robot::leg_type::two_axis,
            utility::robot::side::left,
            arduino,
            calculations,
            hal::hardware::D18,
            hal::hardware::D5),
        leg_factory->create(
            utility::robot::leg_type::two_axis,
            utility::robot::side::left,
            arduino,
            calculations,
            hal::hardware::D17,
            hal::hardware::D16),
        leg_factory->create(
            utility::robot::leg_type::two_axis,
            utility::robot::side::right,
            arduino,
            calculations,
            hal::hardware::D26,
            hal::hardware::D27),
        leg_factory->create(
            utility::robot::leg_type::two_axis,
            utility::robot::side::right,
            arduino,
            calculations,
            hal::hardware::D33,
            hal::hardware::D25),
        std::move(config_manager))};

const std::shared_ptr<controller::controller> robot_controller{
    controller::controller::create(
        dog,
        gamepad,
        executer,
        arduino)};

// const std::unique_ptr<robot::leg> leg{
//     leg_factory->create(
//         utility::robot::leg_type::two_axis,
//         arduino,
//         calculations,
//         hal::hardware::D18,
//         hal::hardware::D5)};

utility::gamepad::atomic_events gamepad_events{
    {0}, {0}, {false}, {false}, {false}, {false}, {false}, {false}, {false}};

void setup()
{
    arduino->begin(115200);
    gamepad->begin();
    dog->begin();

    xTaskCreatePinnedToCore(
        control_robot,      // Task function.
        "Task1",            // Name of task.
        10000,              // Stack size of task
        NULL,               // Parameter of the task
        0,                  // Priority of the task
        NULL,               // Task handle to keep track of created task
        1);                 // Pin task to core 1
}

void loop()
{
    vTaskDelete(NULL);
}

void ps4_controller_connected()
{
    executer->execute([]()
    {
        gamepad->set_rumble(0, 255);
        gamepad->set_led(255, 0, 0);
        gamepad->send();
        arduino->delay(1000);
        gamepad->set_rumble(0, 0);
        gamepad->set_led(150, 0, 205);
        gamepad->send();
    });
}

void ps4_controller_event(utility::gamepad::events&& events)
{
    if (events.l_stick_y.second)
    {
        gamepad_events.l_stick_y = events.l_stick_y.first;
    }

    if (events.r_stick_y.second)
    {
        gamepad_events.r_stick_y = events.r_stick_y.first;
    }

    gamepad_events.left = events.left;
    gamepad_events.right = events.right;
    gamepad_events.l1 = events.l1;
    gamepad_events.r1 = events.r1;
    gamepad_events.cross = events.cross;
    gamepad_events.circle = events.circle;
    gamepad_events.settings = events.settings;
}

void control_robot(void* params)
{
    while (true)
    {
        robot_controller->on_l_stick_y_move(gamepad_events.l_stick_y);
        robot_controller->on_r_stick_y_move(gamepad_events.r_stick_y);

        // Could miss button presses using this approach

        if (gamepad_events.left)
        {
            gamepad_events.left = false;
            arduino->println("Left");
            robot_controller->on_left_button();
        }

        if (gamepad_events.right)
        {
            gamepad_events.right = false;
            arduino->println("Right");
            robot_controller->on_right_button();
        }

        if (gamepad_events.l1)
        {
            gamepad_events.l1 = false;
            arduino->println("L1");
            robot_controller->on_l1_button();
        }

        if (gamepad_events.r1)
        {
            gamepad_events.r1 = false;
            arduino->println("R1");
            robot_controller->on_r1_button();
        }

        if (gamepad_events.cross)
        {
            gamepad_events.cross = false;
            arduino->println("Cross");
            robot_controller->on_cross_button();
        }

        if (gamepad_events.circle)
        {
            gamepad_events.circle = false;
            arduino->println("Circle");
            robot_controller->on_circle_button();
        }

        if (gamepad_events.settings)
        {
            gamepad_events.settings = false;
            arduino->println("Settings");
            robot_controller->on_settings_button();
        }

        robot_controller->update();
    }
}

// void set_leg_position(void* params)
// {
//     leg->set_leg_straight_down();

//     while(!leg->update_position())
//     {
//     }

//     arduino->println("After while");

//     delay(2000);

//     for (int i = 0; i < 20; ++i)
//     {
//         leg->trim_joint(
//             utility::robot::joint::knee,
//             utility::robot::direction::clockwise);
//         arduino->delay(250);
//     }

//     for (int i = 0; i < 20; ++i)
//     {
//         leg->trim_joint(
//             utility::robot::joint::knee,
//             utility::robot::direction::anti_clockwise);
//         arduino->delay(250);
//     }

//     delay(2000);

//     leg->set_leg_neutral_position();

//     while(!leg->update_position())
//     {
//     }

//     while(true)
//     {
//         leg->set_position(
//             gamepad_events.l_stick_y,
//             gamepad_events.r_stick_y,
//             utility::robot::movement::smooth);
//         leg->update_position();

//         // arduino->println("Before straight down");

//         // leg->set_leg_straight_down();

//         // while(!leg->update_position())
//         // {
//         // }

//         // arduino->println("After while");

//         // delay(5000);

//         // leg->set_leg_neutral_position();

//         // while(!leg->update_position())
//         // {
//         // }

//         // delay(5000);

//         arduino->delay_microseconds(1);
//     }
// }
