#include <gtest/gtest.h>

#include <mathmatics/trigonometry/isosceles_triangle_impl.hpp>

namespace mathmatics
{
namespace trigonometry
{

namespace
{

class IsoscelesTriangleImplTests : public ::testing::TestWithParam<
    std::tuple<uint8_t, float, std::tuple<float, float, float> > >
{
};

}

TEST_P(IsoscelesTriangleImplTests, GenerateAnglesWillReturnCorrectAngles)
{
    isosceles_triangle_impl t(std::get<0>(GetParam()));
    auto angles = t.generate_angles(std::get<1>(GetParam()));
    EXPECT_NEAR(
        std::get<0>(std::get<2>(GetParam())),
        std::get<0>(angles),
        0.001);
    EXPECT_NEAR(
        std::get<1>(std::get<2>(GetParam())),
        std::get<1>(angles),
        0.001);
    EXPECT_NEAR(
        std::get<2>(std::get<2>(GetParam())),
        std::get<2>(angles),
        0.001);
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    IsoscelesTriangleImplTests,
    ::testing::Values(
        std::make_tuple(55, 95.0, std::make_tuple(0.528, 0.528, 2.085)),
        std::make_tuple(55, 95, std::make_tuple(0.528, 0.528, 2.085)),
        std::make_tuple(3, 5.5, std::make_tuple(0.411, 0.411, 2.319))));

}
}
