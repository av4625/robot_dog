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
        int stack_size,
        uint8_t core) override;

    void register_event_handler(
        std::function<void()> func,
        const char* event_base_id,
        int32_t event_id) override;

    void register_event_handler(
        std::function<void(int8_t)> func,
        const char* event_base_id,
        int32_t event_id) override;

    void register_event_handler(
        std::function<void(two_int8s)> func,
        const char* event_base_id,
        int32_t event_id) override;

    void send_event(const event::event& event) override;

private:
    struct event_handler
    {
        virtual ~event_handler(){}
    };

    template <typename T>
    struct event_handler_with_arg : event_handler
    {
        event_handler_with_arg(const std::function<void(T)> f) : f(f)
        {
        }

        std::function<void(T)> f;
    };

    struct event_handler_without_arg : event_handler
    {
        event_handler_without_arg(const std::function<void()> f) : f(f)
        {
        }

        std::function<void()> f;
    };

    esp_event_loop_handle_t loop_handle_;
    std::vector<std::unique_ptr<event_handler> > event_handlers_;

    static void callback(
        void* event_handler_arg,
        const char* event_base,
        int32_t event_id,
        void* event_data);

    template <typename T>
    static void callback(
        void* event_handler_arg,
        const char* event_base,
        int32_t event_id,
        void* event_data);

    template <typename T>
    void register_event_handler(
        std::function<void(T)> func,
        const char* event_base_id,
        int32_t event_id);
};

template <typename T>
void event_loop_impl::callback(
    void* event_handler_arg,
    const char* event_base,
    const int32_t event_id,
    void* event_data)
{
    if (event_handler_arg && event_data)
    {
        const auto f{
            reinterpret_cast<std::function<void(T)>*>(event_handler_arg)};
        (*f)(*reinterpret_cast<T*>(event_data));
    }
}

template <typename T>
void event_loop_impl::register_event_handler(
    const std::function<void(T)> func,
    const char* event_base_id,
    const int32_t event_id)
{
    std::unique_ptr<event_handler> event_handler{
        new event_handler_with_arg<T>{func}};
    event_handler_with_arg<T>* event_handler_ptr{
        static_cast<event_handler_with_arg<T>*>(event_handler.get())};
    event_handlers_.push_back(std::move(event_handler));

    esp_event_handler_register_with(
        loop_handle_,
        event_base_id,
        event_id,
        callback,
        reinterpret_cast<void*>(&(event_handler_ptr->f)));
}

}

#endif
