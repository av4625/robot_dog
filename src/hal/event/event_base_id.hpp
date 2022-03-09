#ifndef EVENT_EVENT_BASE_ID_HPP
#define EVENT_EVENT_BASE_ID_HPP

// Has to be included for esp_event_base.h
#include <cstdint>
#include "esp_event_base.h"

namespace hal
{
namespace event
{

ESP_EVENT_DECLARE_BASE(GAMEPAD_EVENTS);

}
}

#endif
