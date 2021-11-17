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
        interpolation_curve curve) override;

    void start(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve,
        int grain) override;

    int get_value() override;

    bool is_finished() override;

private:
    rampDouble ramp_;
};

}

#endif
