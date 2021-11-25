#include <gtest/gtest.h>

#include <memory>

#include <hal/hardware/arduino_mock.hpp>
#include <mathmatics/smoother_impl.hpp>

namespace mathmatics
{

namespace
{

const uint8_t grain{10};

class SmootherImplTests : public ::testing::Test
{
protected:
    SmootherImplTests() :
        arduino_mock_(std::make_shared<hal::hardware::arduino_mock>()),
        smoother_(arduino_mock_)
    {
    }

    const std::shared_ptr<hal::hardware::arduino_mock> arduino_mock_;
    smoother_impl smoother_;
};

}

TEST_F(SmootherImplTests, IsFinishedWillReturnTrueAsDefault)
{
    EXPECT_TRUE(smoother_.is_finished());
}

TEST_F(SmootherImplTests,
    GetValueWhenNonDefaultGrainAndEqualGrainAndNotFinishedWillCalculateNextValue)
{
    smoother_impl smoother(arduino_mock_, 50);
    smoother.start(0, 100);

    EXPECT_CALL(*arduino_mock_, millis()).WillOnce(::testing::Return(50));

    const auto value = smoother.get_value();

    EXPECT_TRUE((value != 0) && (value != 100));
    EXPECT_FALSE(smoother.is_finished());
}

TEST_F(SmootherImplTests,
    GetValueWhenEqualGrainAndNotFinishedWillCalculateNextValue)
{
    smoother_.start(0, 100);

    EXPECT_CALL(*arduino_mock_, millis()).WillOnce(::testing::Return(grain));

    const auto value = smoother_.get_value();

    EXPECT_TRUE((value != 0) && (value != 100));
    EXPECT_FALSE(smoother_.is_finished());
}

TEST_F(SmootherImplTests,
    GetValueWhenNonDefaultGrainAndBelowGrainAndNotFinishedWillNotCalculateNextValue)
{
    smoother_impl smoother(arduino_mock_, 50);
    smoother.start(0, 100);

    EXPECT_CALL(*arduino_mock_, millis()).WillOnce(::testing::Return(49));

    const auto value = smoother.get_value();

    EXPECT_EQ(0 , value);
    EXPECT_FALSE(smoother.is_finished());
}

TEST_F(SmootherImplTests,
    GetValueWhenBelowGrainAndNotFinishedWillNotCalculateNextValue)
{
    smoother_.start(0, 100);

    EXPECT_CALL(*arduino_mock_, millis()).WillOnce(::testing::Return(grain - 1));

    const auto value = smoother_.get_value();

    EXPECT_EQ(0 , value);
    EXPECT_FALSE(smoother_.is_finished());
}

TEST_F(SmootherImplTests,
    GetValueWhenFinishedWillReturnDestinationAndIsFinished)
{
    smoother_.start(0, 100);

    for(int i = 0; i < 51; ++i)
    {
        EXPECT_CALL(*arduino_mock_, millis())
            .WillOnce(::testing::Return(grain * (i + 1)));
        const auto value = smoother_.get_value();
        EXPECT_TRUE((value != 0) && (value != 100));
        EXPECT_FALSE(smoother_.is_finished());
    }

    auto value = smoother_.get_value();
    EXPECT_EQ(100 , value);
    EXPECT_TRUE(smoother_.is_finished());

    value = smoother_.get_value();
    EXPECT_EQ(100 , value);
    EXPECT_TRUE(smoother_.is_finished());
}

}
