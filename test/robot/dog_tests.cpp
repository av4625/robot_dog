#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <hal/config/manager_mock.hpp>
#include <robot/dog.hpp>

#include "leg_mock.hpp"

namespace robot
{

namespace
{

const utility::config::robot_settings settings{1, 2, 3, 4, 5, 6, 7, 8};

struct update_position_params
{
    update_position_params(
        const bool front_left,
        const bool rear_left,
        const bool front_right,
        const bool rear_right,
        const bool dog_return) :
            front_left(front_left),
            rear_left(rear_left),
            front_right(front_right),
            rear_right(rear_right),
            dog_return(dog_return)
    {
    }

    const bool front_left;
    const bool rear_left;
    const bool front_right;
    const bool rear_right;
    const bool dog_return;
};

class DogTests : public ::testing::Test
{
protected:
    DogTests() :
        front_left_(new leg_mock()),
        front_left_ptr_(dynamic_cast<leg_mock*>(front_left_.get())),
        rear_left_(new leg_mock()),
        rear_left_ptr_(dynamic_cast<leg_mock*>(rear_left_.get())),
        front_right_(new leg_mock()),
        front_right_ptr_(dynamic_cast<leg_mock*>(front_right_.get())),
        rear_right_(new leg_mock()),
        rear_right_ptr_(dynamic_cast<leg_mock*>(rear_right_.get())),
        config_(new hal::config::manager_mock()),
        config_mock_(dynamic_cast<hal::config::manager_mock*>(config_.get())),
        dog_(
            std::move(front_left_),
            std::move(rear_left_),
            std::move(front_right_),
            std::move(rear_right_),
            std::move(config_))
    {
    }

    std::unique_ptr<leg> front_left_;
    leg_mock* front_left_ptr_;
    std::unique_ptr<leg> rear_left_;
    leg_mock* rear_left_ptr_;
    std::unique_ptr<leg> front_right_;
    leg_mock* front_right_ptr_;
    std::unique_ptr<leg> rear_right_;
    leg_mock* rear_right_ptr_;
    std::unique_ptr<hal::config::manager> config_;
    hal::config::manager_mock* config_mock_;
    dog dog_;
};

}

TEST_F(DogTests, BeginWillCallBeginForAllLegs)
{
    EXPECT_CALL(*config_mock_, begin());
    EXPECT_CALL(*config_mock_, get_settings(::testing::_))
        .WillOnce(::testing::SetArgReferee<0>(settings));
    EXPECT_CALL(*front_left_ptr_, begin(1, 2));
    EXPECT_CALL(*rear_left_ptr_, begin(3, 4));
    EXPECT_CALL(*front_right_ptr_, begin(5, 6));
    EXPECT_CALL(*rear_right_ptr_, begin(7, 8));
    dog_.begin();
}

TEST_F(DogTests, SetPositionWillCallSetPositionForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_position(
        1,
        2,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_left_ptr_, set_position(
        1,
        2,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*front_right_ptr_, set_position(
        1,
        2,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_right_ptr_, set_position(
        1,
        2,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    dog_.set_position(1, 2);
}

TEST_F(DogTests, SetHeightWillCallSetHeightForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_height(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_left_ptr_, set_height(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*front_right_ptr_, set_height(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_right_ptr_, set_height(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    dog_.set_height(1);
}

TEST_F(DogTests, SetForwardBackWillCallSetForwardBackForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_forward_back(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_left_ptr_, set_forward_back(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*front_right_ptr_, set_forward_back(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    EXPECT_CALL(*rear_right_ptr_, set_forward_back(
        1,
        ::testing::Matcher<utility::robot::movement>(
            utility::robot::movement::smooth)));

    dog_.set_forward_back(1);
}

class DogTestsUpdatePosition :
    public DogTests,
    public ::testing::WithParamInterface<update_position_params>
{
};

TEST_P(DogTestsUpdatePosition, UpdatePositionWillCallUpdatePositionForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, update_position())
        .WillOnce(::testing::Return(GetParam().front_left));
    EXPECT_CALL(*rear_left_ptr_, update_position())
        .WillOnce(::testing::Return(GetParam().front_right));
    EXPECT_CALL(*front_right_ptr_, update_position())
        .WillOnce(::testing::Return(GetParam().rear_left));
    EXPECT_CALL(*rear_right_ptr_, update_position())
        .WillOnce(::testing::Return(GetParam().rear_right));

    EXPECT_EQ(GetParam().dog_return, dog_.update_position());
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    DogTestsUpdatePosition,
    ::testing::Values(
        update_position_params(true, true, true, true, true),
        update_position_params(false, true, true, true, false),
        update_position_params(true, false, true, true, false),
        update_position_params(true, true, false, true, false),
        update_position_params(true, true, true, false, false),
        update_position_params(false, false, false, false, false)));

TEST_F(DogTests, FullyExtendLegsWillCallSetLegStraightDownForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_leg_straight_down());
    EXPECT_CALL(*rear_left_ptr_, set_leg_straight_down());
    EXPECT_CALL(*front_right_ptr_, set_leg_straight_down());
    EXPECT_CALL(*rear_right_ptr_, set_leg_straight_down());

    dog_.fully_extend_legs();
}

TEST_F(DogTests, SetLegsInNeutralPositionWillSetAlLegsInNeutralPosition)
{
    EXPECT_CALL(*front_left_ptr_, set_leg_neutral_position());
    EXPECT_CALL(*rear_left_ptr_, set_leg_neutral_position());
    EXPECT_CALL(*front_right_ptr_, set_leg_neutral_position());
    EXPECT_CALL(*rear_right_ptr_, set_leg_neutral_position());

    dog_.set_legs_in_neutral_position();
}

class DogTestsTrim :
    public DogTests,
    public ::testing::WithParamInterface<
        std::pair<utility::robot::joint, utility::robot::direction> >
{
};

TEST_P(DogTestsTrim, TrimJointWhenLimbIsFrontLeftWillTrimFrontLeft)
{
    EXPECT_CALL(*front_left_ptr_, trim_joint(
        GetParam().first, GetParam().second))
            .WillOnce(::testing::Return(10));

    dog_.trim_joint(
        utility::robot::limb::front_left,
        GetParam().first,
        GetParam().second);

    // Use save settings to make sure correct setting were saved
    if (GetParam().first == utility::robot::joint::shoulder)
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 10),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }
    else
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 10),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }

    dog_.save_trim_values();
}

TEST_P(DogTestsTrim, TrimJointWhenLimbIsRearLeftWillTrimRearLeft)
{
    EXPECT_CALL(*rear_left_ptr_, trim_joint(
        GetParam().first, GetParam().second))
            .WillOnce(::testing::Return(10));

    dog_.trim_joint(
        utility::robot::limb::rear_left,
        GetParam().first,
        GetParam().second);

    // Use save settings to make sure correct setting were saved
    if (GetParam().first == utility::robot::joint::shoulder)
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 10),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }
    else
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 10),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }

    dog_.save_trim_values();
}

TEST_P(DogTestsTrim, TrimJointWhenLimbIsFrontRightWillTrimFrontRight)
{
    EXPECT_CALL(*front_right_ptr_, trim_joint(
        GetParam().first, GetParam().second))
            .WillOnce(::testing::Return(10));

    dog_.trim_joint(
        utility::robot::limb::front_right,
        GetParam().first,
        GetParam().second);

    // Use save settings to make sure correct setting were saved
    if (GetParam().first == utility::robot::joint::shoulder)
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 10),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }
    else
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 10),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }

    dog_.save_trim_values();
}

TEST_P(DogTestsTrim, TrimJointWhenLimbIsRearRightWillTrimRearRight)
{
    EXPECT_CALL(*rear_right_ptr_, trim_joint(
        GetParam().first, GetParam().second))
            .WillOnce(::testing::Return(10));

    dog_.trim_joint(
        utility::robot::limb::rear_right,
        GetParam().first,
        GetParam().second);

    // Use save settings to make sure correct setting were saved
    if (GetParam().first == utility::robot::joint::shoulder)
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 10),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 0))));
    }
    else
    {
        EXPECT_CALL(*config_mock_, save_settings(
            ::testing::AllOf(
                ::testing::Field(
                    &utility::config::robot_settings::front_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::front_right_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_left_knee, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_shoulder, 0),
                ::testing::Field(
                    &utility::config::robot_settings::rear_right_knee, 10))));
    }

    dog_.save_trim_values();
}

INSTANTIATE_TEST_SUITE_P(
    Values,
    DogTestsTrim,
    ::testing::Values(
        std::make_pair(
            utility::robot::joint::knee,
            utility::robot::direction::clockwise),
        std::make_pair(
            utility::robot::joint::knee,
            utility::robot::direction::anti_clockwise),
        std::make_pair(
            utility::robot::joint::shoulder,
            utility::robot::direction::clockwise),
        std::make_pair(
            utility::robot::joint::shoulder,
            utility::robot::direction::anti_clockwise)));

TEST_F(DogTests, SaveTrimValuesWillSaveSettingsInConfig)
{
    EXPECT_CALL(*config_mock_, save_settings(
        ::testing::AllOf(
            ::testing::Field(
                &utility::config::robot_settings::front_left_shoulder, 0),
            ::testing::Field(
                &utility::config::robot_settings::front_left_knee, 0),
            ::testing::Field(
                &utility::config::robot_settings::front_right_shoulder, 0),
            ::testing::Field(
                &utility::config::robot_settings::front_right_knee, 0),
            ::testing::Field(
                &utility::config::robot_settings::rear_left_shoulder, 0),
            ::testing::Field(
                &utility::config::robot_settings::rear_left_knee, 0),
            ::testing::Field(
                &utility::config::robot_settings::rear_right_shoulder, 0),
            ::testing::Field(
                &utility::config::robot_settings::rear_right_knee, 0))));

    dog_.save_trim_values();
}

}
