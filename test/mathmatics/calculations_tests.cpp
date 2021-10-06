#include <gtest/gtest.h>

#include <mathmatics/calculations.hpp>

namespace mathmatics
{

namespace
{

class CalculationsTests : public ::testing::TestWithParam<
    std::tuple<float, float, float, float, int, int> >
{
protected:
    CalculationsTests() : calc_() {}

    calculations calc_;
};

}

TEST_P(CalculationsTests, MapWillReturnCorrectValue)
{
    EXPECT_NEAR(
        std::get<0>(GetParam()),
        calc_.map(
            std::get<1>(GetParam()),
            std::get<2>(GetParam()),
            std::get<3>(GetParam()),
            std::get<4>(GetParam()),
            std::get<5>(GetParam())),
        0.001);
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    CalculationsTests,
    ::testing::Values(
        std::make_tuple(4, 2, 0, 10, 0, 20),
        std::make_tuple(3, 1.5, 0, 10, 0, 20),
        std::make_tuple(16, 2, 0, 10, 20, 0),
        std::make_tuple(17, 1.5, 0, 10, 20, 0),
        std::make_tuple(0, 0.5, 0.5, 1.5, 0, 10),
        std::make_tuple(10, 1.5, 0.5, 1.5, 0, 10),
        std::make_tuple(1, 0.6, 0.5, 1.5, 0, 10),
        std::make_tuple(0.5, 0.55, 0.5, 1.5, 0, 10),
        std::make_tuple(-5, 5, 0, 10, 0, -10)));

}
