#include <atomic>
#include <memory>
#include <utility>

#include <PS4Controller.h>

#include "src/hal/core_executer.hpp"
#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/gamepad_factory_impl.hpp"
#include "src/hal/robot/leg_factory_impl.hpp"
#include "src/mathmatics/calculations_impl.hpp"
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
        "01:01:01:01:01:01",
        &ps4_controller_connected,
        &ps4_controller_event)};

const std::shared_ptr<hal::executer> executer{
    std::make_shared<hal::core_executer>()};

const std::shared_ptr<const mathmatics::calculations> calculations{
    std::make_shared<const mathmatics::calculations_impl>()};

const std::unique_ptr<hal::robot::leg_factory> leg_factory{
    new hal::robot::leg_factory_impl()};
const std::unique_ptr<robot::leg> leg{
    leg_factory->create(
        utility::robot::leg_type::two_axis,
        arduino,
        calculations,
        hal::hardware::D18,
        hal::hardware::D5)};

utility::gamepad::atomic_events gamepad_events;

void setup()
{
    arduino->begin(115200);
    gamepad->begin();
    leg->begin(40, 100);

    xTaskCreatePinnedToCore(
        set_leg_position,   // Task function.
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

void connected_lights(void* params)
{
    if (gamepad)
    {
        gamepad->set_rumble(0, 255);
        gamepad->set_led(255, 0, 0);
        gamepad->send();
        arduino->delay(1000);
        gamepad->set_rumble(0, 0);
        gamepad->set_led(150, 0, 205);
        gamepad->send();
    }

    vTaskDelete(NULL);
}

void set_leg_position(void* params)
{
    while(true)
    {
        leg->set_position(
            gamepad_events.l_stick_y,
            gamepad_events.r_stick_y,
            utility::robot::movement::smooth);
        leg->update_position();

        // leg->set_leg_straight_down();

        // while(!leg->update_position())
        // {
        // }

        // arduino->println("After while");

        // delay(5000);

        // leg->set_leg_neutral_position();

        // while(!leg->update_position())
        // {
        // }

        // delay(5000);

        arduino->delay_microseconds(1);
    }
}
