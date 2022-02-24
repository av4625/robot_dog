#include "arduino_impl.hpp"

#include "Arduino.h"
#include <ESP32PWM.h>

namespace hal
{
namespace hardware
{

void arduino_impl::begin(const unsigned long serial_baud_rate) const
{
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    Serial.begin(serial_baud_rate);
}

void arduino_impl::pin_mode(const uint8_t pin, const uint8_t mode) const
{
    pinMode(pin, mode);
}

int arduino_impl::digital_read(const uint8_t pin) const
{
    return digitalRead(pin);
}

uint16_t arduino_impl::analog_read(const uint8_t pin) const
{
    return analogRead(pin);
}

unsigned long arduino_impl::millis() const
{
    return ::millis();
}

void arduino_impl::delay(const uint32_t milliseconds) const
{
    ::delay(milliseconds);
}

void arduino_impl::print(const char* message) const
{
    Serial.print(message);
}

void arduino_impl::print(const int message) const
{
    Serial.print(message);
}

void arduino_impl::print(const uint32_t message) const
{
    Serial.print(message);
}

void arduino_impl::print(const double message) const
{
    Serial.print(message);
}

void arduino_impl::println(const char* message) const
{
    Serial.println(message);
}

void arduino_impl::println(const int message) const
{
    Serial.println(message);
}

void arduino_impl::println(const uint32_t message) const
{
    Serial.println(message);
}

void arduino_impl::println(const double message) const
{
    Serial.println(message);
}

}
}
