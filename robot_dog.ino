#include <atomic>
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

#include <ESP32Servo.h>

#include "src/hal/hardware/arduino_impl.hpp"
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
        set_leg_position,   // Task function.
        "Task1",            // Name of task.
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
    static unsigned long current_time{0};
    static input_devices::rotation_direction direction;
    static input_devices::button_press_type press_type;
    static bool height_mode = true;

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
}

int shoulder_microseconds = 0;
int knee_microseconds = 0;

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

    const float right_angle_radians{M_PI / 2};

    uint8_t h{0};
    int8_t f_b{0};
    float shoulder_angle{0};

    while(true)
    {
        h = height;
        f_b = forward_back;

        auto leg_height = forward_back_triangle->calculate_hypotenuse(
            f_b, h);
        auto shoulder_advance = forward_back_triangle->generate_angles(
            f_b, h);

        if (leg_height > 109)
        {
            leg_height = 109;
        }

        auto angles = height_triangle->generate_angles(leg_height);

        shoulder_angle = std::get<0>(angles) + std::get<0>(shoulder_advance);

        shoulder_microseconds = calc.map(
            shoulder_angle, -right_angle_radians, right_angle_radians, 40, 2040);
        knee_microseconds = calc.map(std::get<2>(angles), 0, M_PI, 2600, 600);

        shoulder.writeMicroseconds(shoulder_microseconds);
        knee.writeMicroseconds(knee_microseconds);
        delay(1);
    }
}
