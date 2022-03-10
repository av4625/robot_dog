#ifndef HAL_EVENT_LOOP_IMPL_HPP
#define HAL_EVENT_LOOP_IMPL_HPP

#include "event_loop.hpp"

#include <memory>
#include <vector>

#include "esp_event.h"

namespace hal
{

class event_loop_impl : public event_loop
{
public:
    void begin(
        int queue_size,
        const std::string& name,
        uint8_t priority,
        uint32_t stack_size,
        uint8_t core) override;

    void register_event_handler(
        event_handler handler,
        const std::shared_ptr<const event::event>& event) override;

    void send_event(
        const std::shared_ptr<const event::event>& event,
        void* data,
        const size_t data_size) override;

    void send_event(const std::shared_ptr<const event::event>& event) override;

private:
    esp_event_loop_handle_t loop_handle_;
};

}

#endif
