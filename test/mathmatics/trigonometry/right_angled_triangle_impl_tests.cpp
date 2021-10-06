#include <gtest/gtest.h>

#include <mathmatics/trigonometry/right_angled_triangle_impl.hpp>

namespace mathmatics
{
namespace trigonometry
{

namespace
{

class RightAngledTriangleImplTests : public ::testing::Test
{
protected:
    RightAngledTriangleImplTests() : triangle_() {}
    const right_angled_triangle_impl triangle_;
};

class RightAngledTriangleImplAngleTests :
    public RightAngledTriangleImplTests,
    public ::testing::WithParamInterface<
        std::tuple<float, float, std::tuple<float, float, float> > >
{
};

class RightAngledTriangleImplHypotenuseTests :
    public RightAngledTriangleImplTests,
    public ::testing::WithParamInterface<
        std::tuple<float, float, float> >
{
};

}

TEST_P(RightAngledTriangleImplAngleTests, GenerateAnglesWillReturnCorrectAngles)
{
    auto angles = triangle_.generate_angles(
        std::get<0>(GetParam()), std::get<1>(GetParam()));

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
    RightAngledTriangleImplAngleTests,
    ::testing::Values(
        std::make_tuple(90.0, 48.0, std::make_tuple(1.081, 0.490, 1.571)),
        std::make_tuple(90, 48, std::make_tuple(1.081, 0.490, 1.571)),
        std::make_tuple(3, 5.5, std::make_tuple(0.499, 1.071, 1.571))));

TEST_P(RightAngledTriangleImplHypotenuseTests,
    CalculateHypotenuseWillReturnCorrectLength)
{
    EXPECT_NEAR(
        std::get<2>(GetParam()),
        triangle_.calculate_hypotenuse(
            std::get<0>(GetParam()), std::get<1>(GetParam())),
        0.001);
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    RightAngledTriangleImplHypotenuseTests,
    ::testing::Values(
        std::make_tuple(3, 4, 5),
        std::make_tuple(3.0, 4.0, 5.0),
        std::make_tuple(109, 50, 119.92),
        std::make_tuple(77.973, 81.462, 112.765),
        std::make_tuple(0, 50, 50)));

}
}
