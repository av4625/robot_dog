#ifndef HAL_INTERPOLATION_CURVE_HPP
#define HAL_INTERPOLATION_CURVE_HPP

namespace hal
{

enum class interpolation_curve
{
    NONE                = 0x00,
    LINEAR              = 0x01,
    QUADRATIC_IN        = 0x02,
    QUADRATIC_OUT       = 0x03,
    QUADRATIC_INOUT     = 0x04,
    CUBIC_IN            = 0x05,
    CUBIC_OUT           = 0x06,
    CUBIC_INOUT         = 0x07,
    QUARTIC_IN          = 0x08,
    QUARTIC_OUT         = 0x09,
    QUARTIC_INOUT       = 0x0A,
    QUINTIC_IN          = 0x0B,
    QUINTIC_OUT         = 0x0C,
    QUINTIC_INOUT       = 0x0D,
    SINUSOIDAL_IN       = 0x0E,
    SINUSOIDAL_OUT      = 0x0F,
    SINUSOIDAL_INOUT    = 0x10,
    EXPONENTIAL_IN      = 0x11,
    EXPONENTIAL_OUT     = 0x12,
    EXPONENTIAL_INOUT   = 0x13,
    CIRCULAR_IN         = 0x14,
    CIRCULAR_OUT        = 0x15,
    CIRCULAR_INOUT      = 0x16,
    ELASTIC_IN          = 0x17,
    ELASTIC_OUT         = 0x18,
    ELASTIC_INOUT       = 0x19,
    BACK_IN             = 0x1A,
    BACK_OUT            = 0x1B,
    BACK_INOUT          = 0x1C,
    BOUNCE_IN           = 0x1D,
    BOUNCE_OUT          = 0x1E,
    BOUNCE_INOUT        = 0x1F
};

}

#endif
