#ifndef HAL_EVENT_LOOP_HPP
#define HAL_EVENT_LOOP_HPP

#include <cstdint>
#include <memory>
#include <string>

#include "../event/event.hpp"

namespace hal
{

typedef void (*event_handler)(
    void* event_handler_arg,
    const char* event_base,
    int32_t event_id,
    void* event_data);

class event_loop
{
public:
    virtual ~event_loop(){}

    virtual void begin(
        int queue_size,
        const std::string& name,
        uint8_t priority,
        uint32_t stack_size,
        uint8_t core) = 0;

    virtual void register_event_handler(
        event_handler handler,
        const std::shared_ptr<const event::event>& event) = 0;

    virtual void send_event(
        const std::shared_ptr<const event::event>& event,
        void* data,
        const size_t data_size) = 0;

    virtual void send_event(
        const std::shared_ptr<const event::event>& event) = 0;
};

}

#endif
