#ifndef HAL_INTERPOLATION_MOCK_HPP
#define HAL_INTERPOLATION_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/interpolation.hpp>

namespace hal
{

class interpolation_mock : public interpolation
{
public:
    MOCK_METHOD4(start, void(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve));

    MOCK_METHOD5(start, void(
        int range_start,
        int range_end,
        unsigned long duration,
        interpolation_curve curve,
        int grain));

    MOCK_METHOD0(get_value, int());

    MOCK_METHOD0(is_finished, bool());
};

}

#endif
