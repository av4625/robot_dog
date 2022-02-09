#ifndef HAL_HARDWARE_GAMEPAD_HPP
#define HAL_HARDWARE_GAMEPAD_HPP

#include <cstdint>
#include <functional>
#include <string>

namespace hal
{
namespace hardware
{

// Want to be able to set controller lights and rumble from the controller state machine
// When an event happens I want to call a controller state machine function
// Event loop?
// - When the controller triggers an event, post the appropriate event on my
//   event loop. The handler will call the state machine function. Controller
//   can post to the event loop for lights and rumble?

class gamepad
{
public:
    virtual ~gamepad(){}

    virtual void begin() const = 0;

    virtual void set_rumble(uint8_t small, uint8_t large) const = 0;

    virtual void set_led(uint8_t r, uint8_t g, uint8_t b) const = 0;

    virtual void send() const = 0;
};

}
}

#endif
