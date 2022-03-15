#include <gtest/gtest.h>

#include <memory>

#include <controller/controller.hpp>
#include <hal/executer_mock.hpp>
#include <hal/hardware/arduino_mock.hpp>
#include <hal/hardware/gamepad_mock.hpp>
#include <robot/robot_mock.hpp>

#include "context_mock.hpp"
#include "handlers_mock.hpp"

namespace controller
{

namespace
{

class ControllerTests : public ::testing::Test
{
protected:
    ControllerTests() :
        context_(std::make_shared<context_mock>()),
        handlers_mock_(std::make_shared<handlers_mock>()),
        controller_(context_, handlers_mock_)
    {
    }

    const std::shared_ptr<context> context_;
    const std::shared_ptr<handlers_mock> handlers_mock_;
    controller controller_;
};

}

TEST_F(ControllerTests, CreateWillCreateAController)
{
    const auto controller{
        controller::create(
            std::make_shared<robot::robot_mock>(),
            std::make_shared<hal::hardware::gamepad_mock>(),
            std::make_shared<hal::executer_mock>(),
            std::make_shared<hal::hardware::arduino_mock>())};

    const auto deref{*controller};

    EXPECT_EQ(typeid(controller_), typeid(deref));
}

TEST_F(ControllerTests, OnLStickYMoveWillCallStateOnLStickYMove)
{
    const int8_t y(25);

    EXPECT_CALL(*handlers_mock_, on_l_stick_y_move(context_, y));

    controller_.on_l_stick_y_move(y);
}

TEST_F(ControllerTests, OnRStickYMoveWillCallOnRStickYMove)
{
    const int8_t y(25);

    EXPECT_CALL(*handlers_mock_, on_r_stick_y_move(context_, y));

    controller_.on_r_stick_y_move(y);
}

TEST_F(ControllerTests, OnL2MoveWillCallStateOnL2Move)
{
    const uint8_t location(200);

    EXPECT_CALL(*handlers_mock_, on_l2_move(context_, location));

    controller_.on_l2_move(location);
}

TEST_F(ControllerTests, OnR2MoveWillCallOnR2Move)
{
    const uint8_t location(201);

    EXPECT_CALL(*handlers_mock_, on_r2_move(context_, location));

    controller_.on_r2_move(location);
}

TEST_F(ControllerTests, OnLeftButtonWillCallOnLeftButton)
{
    EXPECT_CALL(*handlers_mock_, on_left_button(context_));

    controller_.on_left_button();
}

TEST_F(ControllerTests, OnRightButtonWillCallOnRightButton)
{
    EXPECT_CALL(*handlers_mock_, on_right_button(context_));

    controller_.on_right_button();
}

TEST_F(ControllerTests, OnL1ButtonWillCallOnL1Button)
{
    EXPECT_CALL(*handlers_mock_, on_l1_button(context_));

    controller_.on_l1_button();
}

TEST_F(ControllerTests, OnR1ButtonWillCallOnR1Button)
{
    EXPECT_CALL(*handlers_mock_, on_r1_button(context_));

    controller_.on_r1_button();
}

TEST_F(ControllerTests, OnCrossButtonWillCallOnCrossButton)
{
    EXPECT_CALL(*handlers_mock_, on_cross_button(context_));

    controller_.on_cross_button();
}

TEST_F(ControllerTests, OnCircleButtonWillCallOnCircleButton)
{
    EXPECT_CALL(*handlers_mock_, on_circle_button(context_));

    controller_.on_circle_button();
}

TEST_F(ControllerTests, OnSettingsButtonWillCallOnSettingsButton)
{
    EXPECT_CALL(*handlers_mock_, on_settings_button(context_));

    controller_.on_settings_button();
}

TEST_F(ControllerTests, UpdateWillCallUpdate)
{
    EXPECT_CALL(*handlers_mock_, update(context_));

    controller_.update();
}

}
