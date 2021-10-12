#ifndef HAL_INTERPOLATION_HPP
#define HAL_INTERPOLATION_HPP

#include "interpolation_curve.hpp"

namespace hal
{

class interpolation
{
public:
    virtual ~interpolation(){}

    virtual void start(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve) = 0;

    virtual void start(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve,
        int grain) = 0;

    virtual int get_value() = 0;

    virtual bool is_finished() = 0;
};

}

#endif
