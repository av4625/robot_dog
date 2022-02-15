#ifndef HAL_INTERPOLATION_MOCK_HPP
#define HAL_INTERPOLATION_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/interpolation.hpp>

namespace hal
{

class interpolation_mock : public interpolation
{
public:
    MOCK_METHOD(
        void,
        start,
        (
            int range_start,
            int range_end,
            unsigned long duration,
            interpolation_curve curve
        ),
        (override));

    MOCK_METHOD(
        void,
        start,
        (
            int range_start,
            int range_end,
            unsigned long duration,
            interpolation_curve curve,
            int grain
        ),
        (override));

    MOCK_METHOD(int, get_value, (), (override));

    MOCK_METHOD(bool, is_finished, (), (override));
};

}

#endif
