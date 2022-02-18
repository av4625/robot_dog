#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <robot/dog.hpp>

#include "leg_mock.hpp"

namespace robot
{

namespace
{

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

}

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
        1, 2, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_left_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*front_right_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_right_ptr_, set_position(
        1, 2, ::testing::Matcher<movement>(movement::smooth)));

    dog_.set_position(1, 2);
}

TEST_F(DogTests, SetHeightWillCallSetHeightForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_height(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_left_ptr_, set_height(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*front_right_ptr_, set_height(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_right_ptr_, set_height(
        1, ::testing::Matcher<movement>(movement::smooth)));

    dog_.set_height(1);
}

TEST_F(DogTests, SetForwardBackWillCallSetForwardBackForAllLegs)
{
    EXPECT_CALL(*front_left_ptr_, set_forward_back(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_left_ptr_, set_forward_back(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*front_right_ptr_, set_forward_back(
        1, ::testing::Matcher<movement>(movement::smooth)));
    EXPECT_CALL(*rear_right_ptr_, set_forward_back(
        1, ::testing::Matcher<movement>(movement::smooth)));

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

}
