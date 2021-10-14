#include <atomic>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

#include <ESP32Servo.h>

#include "src/hal/hardware/arduino_impl.hpp"
#include "src/hal/interpolation_impl.hpp"
#include "src/input_devices/potentiometer.hpp"
#include "src/input_devices/rotary_encoder.hpp"
#include "src/input_devices/rotary_encoder_states.hpp"
#include "src/mathmatics/trigonometry/isosceles_triangle_impl.hpp"
#include "src/mathmatics/trigonometry/right_angled_triangle_impl.hpp"
#include "src/mathmatics/calculations.hpp"

Servo shoulder;
Servo knee;

const std::shared_ptr<hal::hardware::arduino> arduino{
    std::make_shared<hal::hardware::arduino_impl>()};
input_devices::rotary_encoder<
    input_devices::rotary_encoder_type::ky040> rotary{
        hal::hardware::D27, hal::hardware::D25, hal::hardware::D32, arduino};

std::atomic<int8_t> forward_back{0};
std::atomic<uint8_t> height{40};

void setup()
{
    arduino->begin(115200);
    rotary.begin();

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    shoulder.setPeriodHertz(50);
    knee.setPeriodHertz(50);
    shoulder.attach(hal::hardware::D18, 500, 2500);
    knee.attach(hal::hardware::D5, 500, 2500);

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
        forward_back = 30;
        delay(1250);
        forward_back = -30;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = 95;
        delay(1250);
        forward_back = 30;
        delay(1250);
        forward_back = -30;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = 67;
        delay(1250);
        forward_back = 30;
        delay(1250);
        forward_back = -30;
        delay(1250);
        forward_back = 0;
        delay(1250);
        height = 40;
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
    const std::shared_ptr<
        mathmatics::trigonometry::right_angled_triangle> forward_back_triangle{
            std::make_shared<
                mathmatics::trigonometry::right_angled_triangle_impl>()};
    const std::shared_ptr<
        mathmatics::trigonometry::isosceles_triangle> height_triangle{
            std::make_shared<
                mathmatics::trigonometry::isosceles_triangle_impl>(55)};
    const mathmatics::calculations calc;
    const std::unique_ptr<hal::interpolation> shoulder_interpolation{
        new hal::interpolation_impl()};
    const std::unique_ptr<hal::interpolation> knee_interpolation{
        new hal::interpolation_impl()};

    const float right_angle_radians{M_PI / 2};

    float shoulder_angle{0};
    short shoulder_microseconds{0};
    short knee_microseconds{0};
    short previous_shoulder_microseconds{0};
    short previous_knee_microseconds{0};
    int8_t current_forward_back{0};
    uint8_t current_height{0};
    int8_t previous_forward_back{0};
    uint8_t previous_height{0};

    while(true)
    {
        if (height != previous_height || forward_back != previous_forward_back)
        {
            current_height = height;
            current_forward_back = forward_back;

            auto leg_height = forward_back_triangle->calculate_hypotenuse(
                current_forward_back, current_height);
            const auto shoulder_advance = forward_back_triangle->generate_angles(
                current_forward_back, current_height);

            if (leg_height > 109)
            {
                leg_height = 109;
            }

            const auto angles = height_triangle->generate_angles(leg_height);

            shoulder_angle = std::get<0>(angles) + std::get<0>(shoulder_advance);

            shoulder_microseconds = calc.map(
                shoulder_angle, -right_angle_radians, right_angle_radians, 40, 2040);
            knee_microseconds = calc.map(std::get<2>(angles), 0, M_PI, 2600, 600);

            const short knee_movement_time{
                fabs(knee_microseconds - previous_knee_microseconds) / 4};
            const short shoulder_movement_time{
                fabs(shoulder_microseconds - previous_shoulder_microseconds) / 4};

            shoulder_interpolation->start(
                previous_shoulder_microseconds,
                shoulder_microseconds,
                (knee_movement_time > shoulder_movement_time) ?
                    knee_movement_time : shoulder_movement_time,
                hal::interpolation_curve::SINUSOIDAL_OUT);
            shoulder.writeMicroseconds(shoulder_interpolation->get_value());

            knee_interpolation->start(
                previous_knee_microseconds,
                knee_microseconds,
                (knee_movement_time > shoulder_movement_time) ?
                    knee_movement_time : shoulder_movement_time,
                hal::interpolation_curve::SINUSOIDAL_OUT);
            knee.writeMicroseconds(knee_interpolation->get_value());

            previous_height = current_height;
            previous_forward_back = current_forward_back;
            previous_shoulder_microseconds = shoulder_microseconds;
            previous_knee_microseconds = knee_microseconds;
        }

        if (!knee_interpolation->is_finished() ||
            !shoulder_interpolation->is_finished())
        {
            shoulder.writeMicroseconds(shoulder_interpolation->get_value());
            knee.writeMicroseconds(knee_interpolation->get_value());
        }

        delay(1);
    }
}
