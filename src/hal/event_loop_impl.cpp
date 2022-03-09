#include "event_loop_impl.hpp"

namespace hal
{

void event_loop_impl::begin(
    const int queue_size,
    const std::string& name,
    const uint8_t priority,
    const int stack_size,
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
    const std::function<void()> func,
    const char* event_base_id,
    const int32_t event_id)
{
    std::unique_ptr<event_handler> event_handler{
        new event_handler_without_arg{func}};
    event_handler_without_arg* event_handler_ptr{
        static_cast<event_handler_without_arg*>(event_handler.get())};
    event_handlers_.push_back(std::move(event_handler));

    esp_event_handler_register_with(
        loop_handle_,
        event_base_id,
        event_id,
        callback,
        reinterpret_cast<void*>(&(event_handler_ptr->f)));
}

void event_loop_impl::register_event_handler(
    const std::function<void(int8_t)> func,
    const char* event_base_id,
    const int32_t event_id)
{
    register_event_handler<int8_t>(func, event_base_id, event_id);
}

void event_loop_impl::register_event_handler(
    const std::function<void(two_int8s)> func,
    const char* event_base_id,
    const int32_t event_id)
{
    register_event_handler<two_int8s>(func, event_base_id, event_id);
}

void event_loop_impl::send_event(const event::event& event)
{
    // esp_event_post_to(
    //     loop_handle_,
    //     event.get_event_base_id(),
    //     event.get_event_id(),
    //     event.data(),
    //     sizeof(event.data()),
    //     portMAX_DELAY);
}

void event_loop_impl::callback(
    void* event_handler_arg,
    const char* event_base,
    const int32_t event_id,
    void* event_data)
{
    if (event_handler_arg)
    {
        const auto f{
            reinterpret_cast<std::function<void()>*>(event_handler_arg)};
        (*f)();
    }
}

}
