#include <gtest/gtest.h>

#include <memory>

#include <controller/context_impl.hpp>
#include <hal/executer_mock.hpp>
#include <hal/hardware/arduino_mock.hpp>
#include <hal/hardware/gamepad_mock.hpp>
#include <robot/robot_mock.hpp>

#include "state_mock.hpp"
#include "state_store_mock.hpp"

namespace controller
{

namespace
{

class ContextTests : public ::testing::Test
{
protected:
    ContextTests() :
        initial_state_mock_(new state_mock()),
        new_state_mock_(new state_mock()),
        state_store_mock_(std::make_shared<state_store_mock>()),
        robot_mock_(std::make_shared<robot::robot_mock>()),
        gamepad_mock_(std::make_shared<hal::hardware::gamepad_mock>()),
        executer_mock_(std::make_shared<hal::executer_mock>()),
        arduino_mock_(std::make_shared<hal::hardware::arduino_mock>())
    {
        EXPECT_CALL(*state_store_mock_, get_initial_state())
            .WillOnce(::testing::Return(initial_state_mock_.get()));

        context_ = std::make_shared<context_impl>(
            state_store_mock_,
            robot_mock_,
            gamepad_mock_,
            executer_mock_,
            arduino_mock_);
    }

    const std::unique_ptr<state_mock> initial_state_mock_;
    const std::unique_ptr<state_mock> new_state_mock_;
    const std::shared_ptr<state_store_mock> state_store_mock_;
    const std::shared_ptr<robot::robot_mock> robot_mock_;
    const std::shared_ptr<hal::hardware::gamepad_mock> gamepad_mock_;
    const std::shared_ptr<hal::executer_mock> executer_mock_;
    const std::shared_ptr<hal::hardware::arduino_mock> arduino_mock_;
    std::shared_ptr<context> context_;
};

}

TEST_F(ContextTests, GetStateWillReturnInitialState)
{
    const state& returned_state(context_->get_state());
    EXPECT_EQ(typeid(state_mock).name(), typeid(returned_state).name());
}

TEST_F(ContextTests, SetStateWillSetANewState)
{
    const state_id id(state_id::lean);

    EXPECT_CALL(*initial_state_mock_, on_exit(::testing::_));
    EXPECT_CALL(*new_state_mock_, on_entry(::testing::_));

    EXPECT_CALL(*state_store_mock_, get_state(id))
        .WillOnce(::testing::Return(new_state_mock_.get()));

    context_->set_state(id);
}

TEST_F(ContextTests, SetGamepadLightColourWillSetLedAndSend)
{
    const uint8_t r{1};
    const uint8_t g{2};
    const uint8_t b{3};

    EXPECT_CALL(*gamepad_mock_, set_led(r, g, b));
    EXPECT_CALL(*gamepad_mock_, send());

    context_->set_gamepad_light_colour(r, g, b);
}

TEST_F(ContextTests,
    SmallRumbleControllerWillUseAnExecuterToRumbleTheController)
{
    EXPECT_CALL(*executer_mock_, execute(::testing::_))
        .WillOnce(::testing::InvokeArgument<0>());
    EXPECT_CALL(*gamepad_mock_, set_rumble(255, 0));
    EXPECT_CALL(*gamepad_mock_, set_rumble(0, 0));
    EXPECT_CALL(*gamepad_mock_, send()).Times(2);
    EXPECT_CALL(*arduino_mock_, delay(500));

    context_->small_rumble_controller(500);
}

TEST_F(ContextTests,
    LargeRumbleControllerWillUseAnExecuterToRumbleTheController)
{
    EXPECT_CALL(*executer_mock_, execute(::testing::_))
        .WillOnce(::testing::InvokeArgument<0>());
    EXPECT_CALL(*gamepad_mock_, set_rumble(0, 255));
    EXPECT_CALL(*gamepad_mock_, set_rumble(0, 0));
    EXPECT_CALL(*gamepad_mock_, send()).Times(2);
    EXPECT_CALL(*arduino_mock_, delay(500));

    context_->large_rumble_controller(500);
}

}
