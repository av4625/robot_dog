#include <memory>
#include <utility>

#include "src/controller/controller.hpp"

#include "src/event/gamepad/circle_button.hpp"
#include "src/event/gamepad/cross_button.hpp"
#include "src/event/gamepad/l_stick_x_move.hpp"
#include "src/event/gamepad/l_stick_y_move.hpp"
#include "src/event/gamepad/l1_button.hpp"
#include "src/event/gamepad/l2_button.hpp"
#include "src/event/gamepad/left_button.hpp"
#include "src/event/gamepad/r_stick_x_move.hpp"
#include "src/event/gamepad/r_stick_y_move.hpp"
#include "src/event/gamepad/r1_button.hpp"
#include "src/event/gamepad/r2_button.hpp"
#include "src/event/gamepad/right_button.hpp"
#include "src/event/gamepad/settings_button.hpp"

#include "src/hal/core_executer.hpp"
#include "src/hal/event_loop_impl.hpp"
#include "src/hal/config/manager_impl.hpp"
#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/gamepad_factory_impl.hpp"
#include "src/hal/robot/leg_factory_impl.hpp"

#include "src/mathmatics/calculations_impl.hpp"

#include "src/robot/dog.hpp"

void ps4_controller_connected();

void on_circle_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_cross_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_l_stick_x_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_l_stick_y_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_l1_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_l2_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_left_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_r_stick_x_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_r_stick_y_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_r1_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_r2_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_right_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

void on_settings_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

const std::shared_ptr<hal::event_loop> event_loop{
    std::make_shared<hal::event_loop_impl>()};

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};

const std::shared_ptr<hal::hardware::gamepad_factory> gamepad_factory{
    std::make_shared<hal::hardware::gamepad_factory_impl>()};
const std::shared_ptr<hal::hardware::gamepad> gamepad{
    gamepad_factory->create_ps4_gamepad(
        "00:02:03:04:05:06",
        &ps4_controller_connected,
        event_loop)};

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
        std::move(config_manager),
        calculations)};

const std::shared_ptr<controller::controller> robot_controller{
    controller::controller::create(
        dog,
        gamepad,
        executer,
        arduino)};

void setup()
{
    event_loop->begin(20, "Main Loop", 8, 10000, 1);

    event_loop->register_event_handler(
        on_circle_button, std::make_shared<event::gamepad::circle_button>());
    event_loop->register_event_handler(
        on_cross_button, std::make_shared<event::gamepad::cross_button>());
    event_loop->register_event_handler(
        on_l_stick_x_move, std::make_shared<event::gamepad::l_stick_x_move>());
    event_loop->register_event_handler(
        on_l_stick_y_move, std::make_shared<event::gamepad::l_stick_y_move>());
    event_loop->register_event_handler(
        on_l1_button, std::make_shared<event::gamepad::l1_button>());
    event_loop->register_event_handler(
        on_l2_button, std::make_shared<event::gamepad::l2_button>());
    event_loop->register_event_handler(
        on_left_button, std::make_shared<event::gamepad::left_button>());
    event_loop->register_event_handler(
        on_r_stick_x_move, std::make_shared<event::gamepad::r_stick_x_move>());
    event_loop->register_event_handler(
        on_r_stick_y_move, std::make_shared<event::gamepad::r_stick_y_move>());
    event_loop->register_event_handler(
        on_r1_button, std::make_shared<event::gamepad::r1_button>());
    event_loop->register_event_handler(
        on_r2_button, std::make_shared<event::gamepad::r2_button>());
    event_loop->register_event_handler(
        on_right_button, std::make_shared<event::gamepad::right_button>());
    event_loop->register_event_handler(
        on_settings_button, std::make_shared<event::gamepad::settings_button>());

    arduino->begin(115200);
    gamepad->begin();
    dog->begin();

    xTaskCreatePinnedToCore(
        robot_updater,        // Task function.
        "Robot Updater Loop", // Name of task.
        10000,                // Stack size of task
        NULL,                 // Parameter of the task
        8,                    // Priority of the task
        NULL,                 // Task handle to keep track of created task
        1);                   // Pin task to core 1
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

void robot_updater(void* params)
{
    while (true)
    {
        // arduino->println("Updating");
        robot_controller->update();
        /* Try removing this (with the priority the same as the event loop the
           delay should allow it to run after each update) */
        arduino->delay_microseconds(1);
    }
}

void on_circle_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("Circle");
    robot_controller->on_circle_button();
}

void on_cross_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("Cross");
    robot_controller->on_cross_button();
}

void on_l_stick_x_move(
    void* event_handler_arg,
    const char* event_base,
    const int32_t event_id,
    void* event_data)
{
    // arduino->println("L Stick");
    if (event_data)
    {
        robot_controller->on_l_stick_x_move(
            *reinterpret_cast<int8_t*>(event_data));
    }
}

void on_l_stick_y_move(
    void* event_handler_arg,
    const char* event_base,
    const int32_t event_id,
    void* event_data)
{
    // arduino->println("L Stick");
    if (event_data)
    {
        robot_controller->on_l_stick_y_move(
            *reinterpret_cast<int8_t*>(event_data));
    }
}

void on_l1_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("L1");
    robot_controller->on_l1_button();
}

void on_l2_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    // arduino->println("L2");
    if (event_data)
    {
        robot_controller->on_l2_move(*reinterpret_cast<uint8_t*>(event_data));
    }
}

void on_left_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("Left");
    robot_controller->on_left_button();
}

void on_r_stick_x_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    // arduino->println("R Stick");
    if (event_data)
    {
        robot_controller->on_r_stick_x_move(
            *reinterpret_cast<int8_t*>(event_data));
    }
}

void on_r_stick_y_move(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    // arduino->println("R Stick");
    if (event_data)
    {
        robot_controller->on_r_stick_y_move(
            *reinterpret_cast<int8_t*>(event_data));
    }
}

void on_r1_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("R1");
    robot_controller->on_r1_button();
}

void on_r2_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    // arduino->println("R2");
    if (event_data)
    {
        robot_controller->on_r2_move(*reinterpret_cast<uint8_t*>(event_data));
    }
}

void on_right_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("Right");
    robot_controller->on_right_button();
}

void on_settings_button(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data)
{
    arduino->println("Settings");
    robot_controller->on_settings_button();
}
