#include "smoother_impl.hpp"
#include <cmath>

namespace mathmatics
{

smoother_impl::smoother_impl(
    const std::shared_ptr<hal::hardware::arduino>& arduino,
    const uint8_t grain) :
        arduino_(arduino),
        grain_(grain),
        destination_(0),
        previous_value_time_(0),
        previous_smoothed_value_(0),
        finished_(true)
{
}

void smoother_impl::start(const short start, const short destination)
{
    previous_smoothed_value_ = start;
    destination_ = destination;
    finished_ = false;
}

short smoother_impl::get_value()
{
    if (fabs(destination_ - previous_smoothed_value_) <= 0.5)
    {
        finished_ = true;
        return destination_;
    }

    const auto current_time{arduino_->millis()};

    if (current_time >= previous_value_time_ + grain_)
    {
        previous_value_time_ = current_time;
        previous_smoothed_value_ = (destination_ * 0.1) +
            (previous_smoothed_value_ * 0.90);
    }

    return previous_smoothed_value_;
}

bool smoother_impl::is_finished() const
{
    return finished_;
}

}
