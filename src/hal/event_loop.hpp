#ifndef HAL_EVENT_LOOP_HPP
#define HAL_EVENT_LOOP_HPP

#include <cstdint>
#include <functional>
#include <string>

#include "../event/event.hpp"

namespace hal
{

struct two_int8s
{
    int8_t first;
    int8_t second;
};

class event_loop
{
public:
    virtual ~event_loop(){}

    virtual void begin(
        int queue_size,
        const std::string& name,
        uint8_t priority,
        int stack_size,
        uint8_t core) = 0;

    virtual void register_event_handler(
        std::function<void()> func,
        const char* event_base_id,
        int32_t event_id) = 0;

    virtual void register_event_handler(
        std::function<void(int8_t)> func,
        const char* event_base_id,
        int32_t event_id) = 0;

    virtual void register_event_handler(
        std::function<void(two_int8s)> func,
        const char* event_base_id,
        int32_t event_id) = 0;

    virtual void send_event(const event::event& event) = 0;
};

}

#endif
