#ifndef HAL_INTERPOLATION_IMPL_HPP
#define HAL_INTERPOLATION_IMPL_HPP

#include "interpolation.hpp"

#include <Ramp.h>

namespace hal
{

class interpolation_impl : public interpolation
{
public:
    void start(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve);

    void start(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve,
        int grain);

    int get_value();

    bool is_finished();

private:
    rampDouble ramp_;
};

}

#endif
