#include <atomic>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

#include <ESP32Servo.h>
#include <PS4Controller.h>

#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/hardware/servo_impl.hpp"
#include "src/hal/interpolation_impl.hpp"
#include "src/input_devices/potentiometer.hpp"
#include "src/input_devices/rotary_encoder.hpp"
#include "src/input_devices/rotary_encoder_states.hpp"
#include "src/mathmatics/trigonometry/isosceles_triangle_impl.hpp"
#include "src/mathmatics/trigonometry/right_angled_triangle_impl.hpp"
#include "src/mathmatics/calculations.hpp"
#include "src/robot/two_axis_leg.hpp"

Servo shoulder;
Servo knee;

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};
input_devices::rotary_encoder<
    input_devices::rotary_encoder_type::ky040> rotary{
        hal::hardware::D27, hal::hardware::D25, hal::hardware::D32, arduino};

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
        std::make_shared<const mathmatics::calculations>())};

std::atomic<int8_t> forward_back{0};
std::atomic<int8_t> height{0};

void setup()
{
    arduino->begin(115200);
    PS4.begin("01:01:01:01:01:01");
    rotary.begin();

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    leg->begin(hal::hardware::D18, hal::hardware::D5);

    xTaskCreatePinnedToCore(
        move_leg,           // Task function.
        "Task1",            // Name of task.
        10000,              // Stack size of task
        NULL,               // Parameter of the task
        0,                  // Priority of the task
        NULL,               // Task handle to keep track of created task
        1);                 // Pin task to core 0

    xTaskCreatePinnedToCore(
        set_leg_position,   // Task function.
        "Task2",            // Name of task.
        10000,              // Stack size of task
        NULL,               // Parameter of the task
        0,                  // Priority of the task
        NULL,               // Task handle to keep track of created task
        0);                 // Pin task to core 0
}

long pot_value = 0;
int loop_count = 0;

void loop()
{
    vTaskDelete(NULL);
}

void move_leg(void* params)
{
    while(true)
    {
        delay(1250);
        forward_back = INT8_MAX;
        delay(1250);
        forward_back = INT8_MIN;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = INT8_MAX;
        delay(1250);
        forward_back = INT8_MAX;
        delay(1250);
        forward_back = INT8_MIN;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = 0;
        delay(1250);
        forward_back = INT8_MAX;
        delay(1250);
        forward_back = INT8_MIN;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = INT8_MIN;
    }
}

void rotary_listener(void* params)
{
    unsigned long current_time{0};
    input_devices::rotation_direction direction;
    input_devices::button_press_type press_type;
    bool height_mode = true;

    while(true)
    {
        current_time = millis();
        direction = rotary.check_rotary(current_time);
        press_type = rotary.check_button(current_time);

        if (height_mode)
        {
            if (height > 40 && direction == input_devices::rotation_direction::left)
            {
                --height;
            }
            else if (height < 95 && direction == input_devices::rotation_direction::right)
            {
                ++height;
            }
        }
        else
        {
            if (forward_back > -30 && direction == input_devices::rotation_direction::left)
            {
                --forward_back;
            }
            else if (forward_back < 30 && direction == input_devices::rotation_direction::right)
            {
                ++forward_back;
            }
        }

        if (press_type == input_devices::button_press_type::button_press)
        {
            height_mode = !height_mode;
        }

        delay(1);
    }
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
