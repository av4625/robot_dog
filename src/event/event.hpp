#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include <cstdint>

namespace event
{

class event
{
public:
    virtual const char* get_event_base_id() const = 0;
    virtual int32_t get_event_id() const = 0;
};

}

#endif
