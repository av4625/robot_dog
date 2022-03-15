#include <gtest/gtest.h>

#include <memory>

#include <controller/state_trim.hpp>
#include <robot/robot_mock.hpp>

#include "context_mock.hpp"

namespace controller
{

namespace
{

class StateTrimTests : public ::testing::Test
{
protected:
    StateTrimTests() :
        context_mock_(std::make_shared<context_mock>()),
        robot_mock_(std::make_shared<robot::robot_mock>()),
        state_trim_()
    {
    }

    const std::shared_ptr<context_mock> context_mock_;
    const std::shared_ptr<robot::robot_mock> robot_mock_;
    state_trim state_trim_;
};

}

TEST_F(StateTrimTests, GetNameWillReturnTrim)
{
    EXPECT_EQ("trim", state_trim_.get_name());
}

TEST_F(StateTrimTests, OnEntryWillSetGamepadAndRobotToTrimMode)
{
    EXPECT_CALL(*context_mock_, large_rumble_controller(1000));
    EXPECT_CALL(*context_mock_, set_gamepad_light_colour(255, 0, 0));

    EXPECT_CALL(*robot_mock_, fully_extend_legs());
    EXPECT_CALL(*robot_mock_, update_position())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_entry(context_mock_);
}

TEST_F(StateTrimTests, OnEntryWillCallUpdateContinuallyUntilUpdateIsFinished)
{
    EXPECT_CALL(*context_mock_, large_rumble_controller(1000));
    EXPECT_CALL(*context_mock_, set_gamepad_light_colour(255, 0, 0));

    EXPECT_CALL(*robot_mock_, fully_extend_legs());
    EXPECT_CALL(*robot_mock_, update_position())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_entry(context_mock_);
}

TEST_F(StateTrimTests, OnExitWillSetRobotToNeutralPosition)
{
    EXPECT_CALL(*robot_mock_, set_legs_in_neutral_position());
    EXPECT_CALL(*robot_mock_, update_position())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_exit(context_mock_);
}

TEST_F(StateTrimTests, OnExitWillCallUpdateContinuallyUntilUpdateIsFinished)
{
    EXPECT_CALL(*robot_mock_, set_legs_in_neutral_position());
    EXPECT_CALL(*robot_mock_, update_position())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_exit(context_mock_);
}

TEST_F(StateTrimTests, OnLStickYMoveWillDoNothing)
{
    const int8_t y{55};
    state_trim_.on_l_stick_y_move(context_mock_, y);
}

TEST_F(StateTrimTests, OnRStickYMoveWillDoNothing)
{
    const int8_t y{55};
    state_trim_.on_r_stick_y_move(context_mock_, y);
}

TEST_F(StateTrimTests, OnL2MoveWillDoNothing)
{
    const uint8_t location{1};
    state_trim_.on_l2_move(context_mock_, location);
}

TEST_F(StateTrimTests, OnR2MoveWillDoNothing)
{
    const uint8_t location{2};
    state_trim_.on_r2_move(context_mock_, location);
}

TEST_F(StateTrimTests, OnLeftButtonWillTrimActiveLimbKneeJointAntiClockwise)
{
    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_left,
        utility::robot::joint::knee,
        utility::robot::direction::anti_clockwise));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_left_button(context_mock_);
}

TEST_F(StateTrimTests, OnRightButtonWillTrimActiveLimbKneeJointClockwise)
{
    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_left,
        utility::robot::joint::knee,
        utility::robot::direction::clockwise));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_right_button(context_mock_);
}

TEST_F(StateTrimTests, OnL1ButtonWillTrimActiveLimbShoulderJointAntiClockwise)
{
    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_left,
        utility::robot::joint::shoulder,
        utility::robot::direction::clockwise));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_l1_button(context_mock_);
}

TEST_F(StateTrimTests, OnR1ButtonWillTrimActiveLimbShoulderJointClockwise)
{
    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_left,
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_trim_.on_r1_button(context_mock_);
}

TEST_F(StateTrimTests, OnCrossButtonWillChangeToNextLimb)
{
    EXPECT_CALL(*context_mock_, get_robot())
        .Times(4).WillRepeatedly(::testing::Return(robot_mock_));
    EXPECT_CALL(*context_mock_, small_rumble_controller(250)).Times(4);

    state_trim_.on_cross_button(context_mock_);

    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::rear_left,
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise));

    state_trim_.on_r1_button(context_mock_);

    state_trim_.on_cross_button(context_mock_);

    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_right,
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise));

    state_trim_.on_r1_button(context_mock_);

    state_trim_.on_cross_button(context_mock_);

    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::rear_right,
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise));

    state_trim_.on_r1_button(context_mock_);

    state_trim_.on_cross_button(context_mock_);

    EXPECT_CALL(*robot_mock_, trim_joint(
        utility::robot::limb::front_left,
        utility::robot::joint::shoulder,
        utility::robot::direction::anti_clockwise));

    state_trim_.on_r1_button(context_mock_);
}

TEST_F(StateTrimTests, OnCircleButtonWillSetStateToLean)
{
    EXPECT_CALL(*context_mock_, set_state(state_id::lean));

    state_trim_.on_circle_button(context_mock_);
}

TEST_F(StateTrimTests, OnSettingsButtonWillSaveSettingsAndSetStateToLean)
{
    EXPECT_CALL(*robot_mock_, save_trim_values());
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));
    EXPECT_CALL(*context_mock_, set_state(state_id::lean));

    state_trim_.on_settings_button(context_mock_);
}

TEST_F(StateTrimTests, UpdateWillDoNothing)
{
    state_trim_.update(context_mock_);
}

}
