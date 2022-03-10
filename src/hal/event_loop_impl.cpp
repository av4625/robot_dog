#include "event_loop_impl.hpp"

namespace hal
{

void event_loop_impl::begin(
    const int queue_size,
    const std::string& name,
    const uint8_t priority,
    const uint32_t stack_size,
    const uint8_t core)
{
    esp_event_loop_args_t loop_args = {
        .queue_size = queue_size,
        .task_name = name.c_str(),
        .task_priority = priority,
        .task_stack_size = stack_size,
        .task_core_id = core
    };

    esp_event_loop_create(&loop_args, &loop_handle_);
}

void event_loop_impl::register_event_handler(
    event_handler handler,
    const std::shared_ptr<const event::event>& event)
{
    esp_event_handler_register_with(
        loop_handle_,
        event->get_event_base_id(),
        event->get_event_id(),
        handler,
        NULL);
}

void event_loop_impl::send_event(
    const std::shared_ptr<const event::event>& event,
    void* data,
    const size_t data_size)
{
    esp_event_post_to(
        loop_handle_,
        event->get_event_base_id(),
        event->get_event_id(),
        data,
        data_size,
        portMAX_DELAY);
}

void event_loop_impl::send_event(
    const std::shared_ptr<const event::event>& event)
{
    send_event(event, NULL, 0);
}

}
