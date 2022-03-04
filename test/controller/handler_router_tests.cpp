#include <gtest/gtest.h>

#include <memory>

#include <controller/handler_router.hpp>

#include "context_mock.hpp"
#include "state_mock.hpp"

namespace controller
{

namespace
{

class HandlerRouterTests : public ::testing::Test
{
protected:
    HandlerRouterTests() :
        context_mock_(std::make_shared<context_mock>()),
        context_(context_mock_),
        state_mock_(),
        handler_router_()
    {
    }

    /** Gtest has a bug with Ref and ReturnRef with shared pointers to non
     * interface types. Solution is to pass in a shared_ptr to the interface and
     * create a raw pointer to the mock for making the EXPECT_CALL's
     */
    const std::shared_ptr<context_mock> context_mock_;
    const std::shared_ptr<context> context_;
    state_mock state_mock_;
    handler_router handler_router_;
};

}

TEST_F(HandlerRouterTests, OnLStickYMoveWillCallActiveStateOnLStickYMove)
{
    const int8_t y(25);

    EXPECT_CALL(state_mock_, on_l_stick_y_move(
        ::testing::Ref(context_), y));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_l_stick_y_move(context_, y);
}

TEST_F(HandlerRouterTests, OnRStickYMoveWillCallActiveStateOnRStickYMove)
{
    const int8_t y(25);

    EXPECT_CALL(state_mock_, on_r_stick_y_move(
        ::testing::Ref(context_), y));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_r_stick_y_move(context_, y);
}

TEST_F(HandlerRouterTests, OnLeftButtonWillCallActiveStateOnLeftButton)
{
    EXPECT_CALL(state_mock_, on_left_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_left_button(context_);
}

TEST_F(HandlerRouterTests, OnRightButtonWillCallActiveStateOnRightButton)
{
    EXPECT_CALL(state_mock_, on_right_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_right_button(context_);
}

TEST_F(HandlerRouterTests, OnL1ButtonWillCallActiveStateOnL1Button)
{
    EXPECT_CALL(state_mock_, on_l1_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_l1_button(context_);
}

TEST_F(HandlerRouterTests, OnR1ButtonWillCallActiveStateOnR1Button)
{
    EXPECT_CALL(state_mock_, on_r1_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_r1_button(context_);
}

TEST_F(HandlerRouterTests, OnCrossButtonWillCallActiveStateOnCrossButton)
{
    EXPECT_CALL(state_mock_, on_cross_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_cross_button(context_);
}

TEST_F(HandlerRouterTests, OnCircleButtonWillCallActiveStateOnCircleButton)
{
    EXPECT_CALL(state_mock_, on_circle_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_circle_button(context_);
}

TEST_F(HandlerRouterTests, OnSettingsButtonWillCallActiveStateOnSettingsButton)
{
    EXPECT_CALL(state_mock_, on_settings_button(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.on_settings_button(context_);
}

TEST_F(HandlerRouterTests, UpdateWillCallActiveStateUpdate)
{
    EXPECT_CALL(state_mock_, update(
        ::testing::Ref(context_)));

    EXPECT_CALL(*context_mock_, get_state())
        .WillOnce(::testing::ReturnRef(state_mock_));

    handler_router_.update(context_);
}

}
