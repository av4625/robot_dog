#include <gtest/gtest.h>

#include <memory>

#include <controller/state_lean.hpp>
#include <robot/robot_mock.hpp>

#include "context_mock.hpp"

namespace controller
{

namespace
{

class StateLeanTests : public ::testing::Test
{
protected:
    StateLeanTests() :
        context_mock_(std::make_shared<context_mock>()),
        robot_mock_(std::make_shared<robot::robot_mock>()),
        state_lean_()
    {
    }

    const std::shared_ptr<context_mock> context_mock_;
    const std::shared_ptr<robot::robot_mock> robot_mock_;
    state_lean state_lean_;
};

}

TEST_F(StateLeanTests, GetNameWillReturnLean)
{
    EXPECT_EQ("lean", state_lean_.get_name());
}

TEST_F(StateLeanTests, OnEntryWillSetGamepad)
{
    EXPECT_CALL(*context_mock_, large_rumble_controller(1000));
    EXPECT_CALL(*context_mock_, set_gamepad_light_colour(0, 0, 255));

    state_lean_.on_entry(context_mock_);
}

TEST_F(StateLeanTests, OnExitWillDoNothing)
{
    state_lean_.on_exit(context_mock_);
}

TEST_F(StateLeanTests, OnLStickXMoveWillSetRobotForwardBack)
{
    const int8_t x{55};

    EXPECT_CALL(*robot_mock_, set_forward_back(x));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_lean_.on_l_stick_x_move(context_mock_, x);
}

TEST_F(StateLeanTests, OnLStickYMoveWillSetRobotHeight)
{
    const int8_t y{55};

    EXPECT_CALL(*robot_mock_, set_height(y));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_lean_.on_l_stick_y_move(context_mock_, y);
}

TEST_F(StateLeanTests, OnRStickXMoveWillSetRobotSideToSideLean)
{
    const int8_t x{55};

    EXPECT_CALL(*robot_mock_, set_side_to_side_lean(x));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_lean_.on_r_stick_x_move(context_mock_, x);
}

TEST_F(StateLeanTests, OnRStickYMoveWillSetRobotForwardBackLean)
{
    const int8_t y{55};

    EXPECT_CALL(*robot_mock_, set_forward_back_lean(y));
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_lean_.on_r_stick_y_move(context_mock_, y);
}

TEST_F(StateLeanTests, OnL2MoveWillDoNothing)
{
    const uint8_t location{1};
    state_lean_.on_l2_move(context_mock_, location);
}

TEST_F(StateLeanTests, OnR2MoveWillDoNothing)
{
    const uint8_t location{2};
    state_lean_.on_r2_move(context_mock_, location);
}

TEST_F(StateLeanTests, OnLeftButtonWillDoNothing)
{
    state_lean_.on_left_button(context_mock_);
}

TEST_F(StateLeanTests, OnRightButtonWillDoNothing)
{
    state_lean_.on_right_button(context_mock_);
}

TEST_F(StateLeanTests, OnL1ButtonWillDoNothing)
{
    state_lean_.on_l1_button(context_mock_);
}

TEST_F(StateLeanTests, OnR1ButtonWillDoNothing)
{
    state_lean_.on_r1_button(context_mock_);
}

TEST_F(StateLeanTests, OnCrossButtonWillDoNothing)
{
    state_lean_.on_cross_button(context_mock_);
}

TEST_F(StateLeanTests, OnCircleButtonWillDoNothing)
{
    state_lean_.on_circle_button(context_mock_);
}

TEST_F(StateLeanTests, OnSettingsButtonWillSetStateToTrim)
{
    EXPECT_CALL(*context_mock_, set_state(state_id::trim));

    state_lean_.on_settings_button(context_mock_);
}

TEST_F(StateLeanTests, UpdateWillUpdateTheRobotPosition)
{
    EXPECT_CALL(*robot_mock_, update_position());
    EXPECT_CALL(*context_mock_, get_robot())
        .WillOnce(::testing::Return(robot_mock_));

    state_lean_.update(context_mock_);
}

}
