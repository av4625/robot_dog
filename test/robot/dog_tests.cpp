#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <robot/dog.hpp>

#include "leg_mock.hpp"

namespace robot
{

namespace
{

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
        dog_(
            std::move(front_left_),
            std::move(rear_left_),
            std::move(front_right_),
            std::move(rear_right_))
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
    dog dog_;
};

TEST_F(DogTests, BeginWillCallBeginForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, begin());
    EXPECT_CALL(*rear_left_ptr_, begin());
    EXPECT_CALL(*front_right_ptr_, begin());
    EXPECT_CALL(*rear_right_ptr_, begin());
    dog_.begin();
}

TEST_F(DogTests, SetPositionWillCallSetPositionForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::interpolation)));
    EXPECT_CALL(*rear_left_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::interpolation)));
    EXPECT_CALL(*front_right_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::interpolation)));
    EXPECT_CALL(*rear_right_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::interpolation)));

    dog_.set_position(1, 2);
}

TEST_F(DogTests, UpdatePositionWillCallUpdatePositionForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, update_position());
    EXPECT_CALL(*rear_left_ptr_, update_position());
    EXPECT_CALL(*front_right_ptr_, update_position());
    EXPECT_CALL(*rear_right_ptr_, update_position());
    dog_.update_position();
}

}

}
