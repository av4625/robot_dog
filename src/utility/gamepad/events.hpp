#ifndef UTILITY_GAMEPAD_EVENTS_HPP
#define UTILITY_GAMEPAD_EVENTS_HPP

#include <cstdint>
#include <utility>

namespace utility
{
namespace gamepad
{

struct events
{
    std::pair<int8_t, bool> l_stick_y;
    std::pair<int8_t, bool> r_stick_y;
    bool settings;
};

}
}

#endif
