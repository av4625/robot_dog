#ifndef MATHMATICS_CALCULATIONS_MOCK_HPP
#define MATHMATICS_CALCULATIONS_MOCK_HPP

#include <gmock/gmock.h>
#include <mathmatics/calculations.hpp>

namespace mathmatics
{

class calculations_mock : public calculations
{
public:
    MOCK_METHOD(
        float,
        map,
        (
            float in,
            float min_in_range,
            float max_in_range,
            int min_out_range,
            int max_out_range
        ),
        (const, override));

    MOCK_METHOD(
        short,
        constrict,
        (
            short value,
            short minimum,
            short maximum
        ),
        (const, override));

    MOCK_METHOD(
        int,
        constrict,
        (
            int value,
            int minimum,
            int maximum
        ),
        (const, override));

    MOCK_METHOD(
        double,
        constrict,
        (
            double value,
            double minimum,
            double maximum
        ),
        (const, override));
};

}

#endif
