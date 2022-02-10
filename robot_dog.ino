#include <atomic>
#include <memory>
#include <utility>

#include <ESP32PWM.h>
#include <PS4Controller.h>

#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/gamepad_factory_impl.hpp"
#include "src/hal/robot/leg_factory_impl.hpp"

void ps4_controller_connected();
void ps4_controller_event(
    std::pair<int8_t, bool>&& forward_back, std::pair<int8_t, bool>&& height);

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};

const std::shared_ptr<hal::hardware::gamepad_factory> gamepad_factory{
    std::make_shared<hal::hardware::gamepad_factory_impl>()};
const std::shared_ptr<hal::hardware::gamepad> gamepad{
    gamepad_factory->create_ps4_gamepad(
        "01:01:01:01:01:01",
        &ps4_controller_connected,
        &ps4_controller_event)};

const std::unique_ptr<hal::robot::leg_factory> leg_factory{
    new hal::robot::leg_factory_impl()};
const std::unique_ptr<robot::leg> leg{
    leg_factory->create(
        robot::leg_type::two_axis,
        arduino,
        hal::hardware::D18,
        hal::hardware::D5)};

std::atomic<int8_t> forward_back{0};
std::atomic<int8_t> height{0};

void setup()
{
    arduino->begin(115200);
    gamepad->begin();

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    leg->begin();

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
    xTaskCreatePinnedToCore(
        connected_lights,   // Task function.
        "Task2",            // Name of task.
        10000,              // Stack size of task
        NULL,               // Parameter of the task
        1,                  // Priority of the task
        NULL,               // Task handle to keep track of created task
        1);                 // Pin task to core 1
}

void ps4_controller_event(
    std::pair<int8_t, bool>&& forward_back, std::pair<int8_t, bool>&& height)
{
    if (forward_back.second)
    {
        ::forward_back = forward_back.first;
    }

    if (height.second)
    {
        ::height = height.first;
    }
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
        leg->set_position(height, forward_back, robot::movement::smooth);
        leg->update_position();

        // Try with micro second delay
        delay(1);
    }
}
