#ifndef UTILITY_GAMEPAD_ATOMIC_EVENTS_HPP
#define UTILITY_GAMEPAD_ATOMIC_EVENTS_HPP

/**
 * Look into "False sharing contention between threads"
 * https://stackoverflow.com/questions/50601726/is-it-ok-to-use-stdatomic-with-a-struct-that-is-pod-except-that-it-has-a-const/50602081
 */

#include <atomic>
#include <cstdint>

namespace utility
{
namespace gamepad
{

struct atomic_events
{
    std::atomic<int8_t> l_stick_y;
    std::atomic<int8_t> r_stick_y;
    std::atomic<bool> settings;
};

}
}

#endif
