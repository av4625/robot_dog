#include "interpolation_impl.hpp"

namespace hal
{

void interpolation_impl::start(
    const int range_start,
    const int range_end,
    const unsigned long duration,
    const interpolation_curve curve)
{
    ramp_.go(range_start);
    ramp_.go(range_end, duration, static_cast<ramp_mode>(curve));
}

void interpolation_impl::start(
    int range_start,
    int range_end,
    unsigned long duration,
    interpolation_curve curve,
    int grain)
{
    ramp_.setGrain(grain);
    start(range_start, range_end, duration, curve);
}

int interpolation_impl::get_value()
{
    return ramp_.update();
}

bool interpolation_impl::is_finished()
{
    return ramp_.isFinished();
}

}
