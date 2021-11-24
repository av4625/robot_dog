#include <atomic>
#include <memory>

#include <PS4Controller.h>

#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/servo_impl.hpp"
#include "src/hal/interpolation_impl.hpp"
#include "src/mathmatics/trigonometry/isosceles_triangle_impl.hpp"
#include "src/mathmatics/trigonometry/right_angled_triangle_impl.hpp"
#include "src/mathmatics/calculations.hpp"
#include "src/robot/two_axis_leg.hpp"

Servo shoulder;
Servo knee;

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};

std::unique_ptr<hal::hardware::servo> shoulder_servo{
    new hal::hardware::servo_impl()};
std::unique_ptr<hal::hardware::servo> knee_servo{
    new hal::hardware::servo_impl()};
std::unique_ptr<hal::interpolation> shoulder_interpolation{
    new hal::interpolation_impl()};
std::unique_ptr<hal::interpolation> knee_interpolation{
    new hal::interpolation_impl()};

const std::unique_ptr<robot::leg> leg{
    new robot::two_axis_leg(
        std::make_shared<
            mathmatics::trigonometry::right_angled_triangle_impl>(),
        std::make_shared<
            mathmatics::trigonometry::isosceles_triangle_impl>(55),
        std::move(shoulder_servo),
        std::move(knee_servo),
        std::move(shoulder_interpolation),
        std::move(knee_interpolation),
        std::make_shared<const mathmatics::calculations>(),
        hal::hardware::D18,
        hal::hardware::D5)};

std::atomic<int8_t> forward_back{0};
std::atomic<int8_t> height{0};

void setup()
{
    arduino->begin(115200);

    PS4.attach(ps4_controller_event);
    PS4.begin("01:01:01:01:01:01");
    PS4.attachOnConnect(ps4_controller_connected);

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

void ps4_controller_event()
{
    if(PS4.event.analog_move.stick.rx)
    {
        forward_back = PS4.data.analog.stick.rx;
    }

    if(PS4.event.analog_move.stick.ly)
    {
        height = PS4.data.analog.stick.ly;
    }
}

void connected_lights(void* params)
{
    PS4.setRumble(0, 255);
    PS4.setLed(255, 0, 0);
    PS4.sendToController();
    arduino->delay(1000);
    PS4.setRumble(0, 0);
    PS4.setLed(150, 0, 205);
    PS4.sendToController();
    vTaskDelete(NULL);
}

void set_leg_position(void* params)
{
    while(true)
    {
        leg->set_position(height, forward_back);
        leg->update_position();

        // Try with micro second delay
        delay(1);
    }
}
