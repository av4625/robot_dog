#include <gtest/gtest.h>

#include <vector>

#include <mathmatics/calculations.hpp>

namespace mathmatics
{

namespace
{

class CalculationsTestsBase : public ::testing::Test
{
protected:
    CalculationsTestsBase() : calc_() {}

    calculations calc_;
};

class CalculationsTestsMap :
    public CalculationsTestsBase,
    public ::testing::WithParamInterface<
        std::tuple<float, float, float, float, int, int> >
{
};

template<class T>
class CalculationsTestsConstrict : public ::testing::Test
{
protected:
    static std::vector<T> values_;
};

typedef ::testing::Types<
    std::tuple<int, int, int, int>,
    std::tuple<float, float, float, float> > TestTypes;

template<> std::vector<std::tuple<int, int, int, int> > CalculationsTestsConstrict<std::tuple<int, int, int, int> >::values_{
    std::make_tuple(1, 1, 1, 10),
    std::make_tuple(1, 0, 1, 10),
    std::make_tuple(10, 10, 1, 10),
    std::make_tuple(10, 11, 1, 10),
    std::make_tuple(5, 5, 1, 10)};
template<> std::vector<std::tuple<float, float, float, float> > CalculationsTestsConstrict<std::tuple<float, float, float, float> >::values_{
    std::make_tuple(1.1, 1.1, 1.1, 10.1),
    std::make_tuple(1.1, 1.0, 1.1, 10.1),
    std::make_tuple(10.1, 10.1, 1.1, 10.1),
    std::make_tuple(10.1, 10.2, 1.1, 10.1),
    std::make_tuple(5.1, 5.1, 1.1, 10.1)};

}

TEST_P(CalculationsTestsMap, MapWillReturnCorrectValue)
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
    CalculationsTestsMap,
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

TYPED_TEST_SUITE_P(CalculationsTestsConstrict);

TYPED_TEST_P(CalculationsTestsConstrict, ConstrictWillReturnCorrectValue)
{
    calculations calc;

    for (TypeParam value : CalculationsTestsConstrict<TypeParam>::values_)
    {
        EXPECT_NEAR(
            std::get<0>(value),
            calc.constrict(
                std::get<1>(value), std::get<2>(value), std::get<3>(value)),
            0.1);
    }
}

REGISTER_TYPED_TEST_SUITE_P(
    CalculationsTestsConstrict, ConstrictWillReturnCorrectValue);

INSTANTIATE_TYPED_TEST_SUITE_P(My, CalculationsTestsConstrict, TestTypes);

}
