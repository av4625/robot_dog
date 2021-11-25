#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <robot/two_axis_leg.hpp>

#include <hal/hardware/servo_mock.hpp>
#include <hal/interpolation_mock.hpp>
#include <mathmatics/smoother_mock.hpp>
#include <mathmatics/trigonometry/isosceles_triangle_mock.hpp>
#include <mathmatics/trigonometry/right_angled_triangle_mock.hpp>

namespace robot
{

namespace
{

const uint8_t shoulder_pin{1};
const uint8_t knee_pin{1};

class TwoAxisLegTests : public ::testing::Test
{
protected:
    TwoAxisLegTests() :
        forward_back_triangle_mock_(std::make_shared<
            const mathmatics::trigonometry::right_angled_triangle_mock>()),
        height_triangle_mock_(std::make_shared<
            const mathmatics::trigonometry::isosceles_triangle_mock>()),
        shoulder_servo_mock_(new hal::hardware::servo_mock()),
        shoulder_servo_mock_ptr_(dynamic_cast<hal::hardware::servo_mock*>(
            shoulder_servo_mock_.get())),
        knee_servo_mock_(new hal::hardware::servo_mock()),
        knee_servo_mock_ptr_(dynamic_cast<hal::hardware::servo_mock*>(
            knee_servo_mock_.get())),
        shoulder_interpolation_mock_(new hal::interpolation_mock()),
        shoulder_interpolation_mock_ptr_(dynamic_cast<hal::interpolation_mock*>(
            shoulder_interpolation_mock_.get())),
        knee_interpolation_mock_(new hal::interpolation_mock()),
        knee_interpolation_mock_ptr_(dynamic_cast<hal::interpolation_mock*>(
            knee_interpolation_mock_.get())),
        shoulder_smoother_mock_(new mathmatics::smoother_mock()),
        shoulder_smoother_mock_ptr_(dynamic_cast<mathmatics::smoother_mock*>(
            shoulder_smoother_mock_.get())),
        knee_smoother_mock_(new mathmatics::smoother_mock()),
        knee_smoother_mock_ptr_(dynamic_cast<mathmatics::smoother_mock*>(
            knee_smoother_mock_.get()))
    {
        EXPECT_CALL(*shoulder_servo_mock_ptr_, get_minimum_time_for_180())
            .Times(2).WillRepeatedly(::testing::Return(500));
        EXPECT_CALL(*knee_servo_mock_ptr_, get_minimum_time_for_180())
            .WillOnce(::testing::Return(499));

        two_axis_leg_.reset(new two_axis_leg(
            forward_back_triangle_mock_,
            height_triangle_mock_,
            std::move(shoulder_servo_mock_),
            std::move(knee_servo_mock_),
            std::move(shoulder_interpolation_mock_),
            std::move(knee_interpolation_mock_),
            std::move(shoulder_smoother_mock_),
            std::move(knee_smoother_mock_),
            std::make_shared<const mathmatics::calculations>(),
            shoulder_pin,
            knee_pin));
    }

    const std::shared_ptr<
        const mathmatics::trigonometry::right_angled_triangle_mock> forward_back_triangle_mock_;
    const std::shared_ptr<
        const mathmatics::trigonometry::isosceles_triangle_mock> height_triangle_mock_;
    std::unique_ptr<hal::hardware::servo> shoulder_servo_mock_;
    hal::hardware::servo_mock* shoulder_servo_mock_ptr_;
    std::unique_ptr<hal::hardware::servo> knee_servo_mock_;
    hal::hardware::servo_mock* knee_servo_mock_ptr_;
    std::unique_ptr<hal::interpolation> shoulder_interpolation_mock_;
    hal::interpolation_mock* shoulder_interpolation_mock_ptr_;
    std::unique_ptr<hal::interpolation> knee_interpolation_mock_;
    hal::interpolation_mock* knee_interpolation_mock_ptr_;
    std::unique_ptr<mathmatics::smoother> shoulder_smoother_mock_;
    mathmatics::smoother_mock* shoulder_smoother_mock_ptr_;
    std::unique_ptr<mathmatics::smoother> knee_smoother_mock_;
    mathmatics::smoother_mock* knee_smoother_mock_ptr_;
    std::unique_ptr<leg> two_axis_leg_;

    void set_max_height_and_forward_interpolation(const int times = 1)
    {
        EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(30, 95))
            .WillOnce(::testing::Return(100));
        EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(30, 95))
            .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
        EXPECT_CALL(*height_triangle_mock_, generate_angles(100))
            .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

        EXPECT_CALL(*shoulder_interpolation_mock_ptr_, start(
            1500,
            ::testing::_,
            ::testing::_,
            ::testing::Matcher<hal::interpolation_curve>(
                hal::interpolation_curve::SINUSOIDAL_OUT)));
        EXPECT_CALL(*knee_interpolation_mock_ptr_, start(
            1500,
            ::testing::_,
            ::testing::_,
            ::testing::Matcher<hal::interpolation_curve>(
                hal::interpolation_curve::SINUSOIDAL_OUT)));

        EXPECT_CALL(*shoulder_interpolation_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(1));
        EXPECT_CALL(*knee_interpolation_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(2));

        EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1)).Times(times);
        EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2)).Times(times);

        two_axis_leg_->set_position(127, 127, movement::interpolation);
    }

    void set_max_height_and_forward_smooth(const int times = 1)
    {
        EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(30, 95))
            .WillOnce(::testing::Return(100));
        EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(30, 95))
            .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
        EXPECT_CALL(*height_triangle_mock_, generate_angles(100))
            .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

        EXPECT_CALL(*shoulder_smoother_mock_ptr_, start(
            1500,
            ::testing::_));
        EXPECT_CALL(*knee_smoother_mock_ptr_, start(
            1500,
            ::testing::_));

        EXPECT_CALL(*shoulder_smoother_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(1));
        EXPECT_CALL(*knee_smoother_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(2));

        EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1)).Times(times);
        EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2)).Times(times);

        two_axis_leg_->set_position(127, 127, movement::smooth);
    }
};

}

TEST_F(TwoAxisLegTests, BeginWillCallBeginForBothServos)
{
    EXPECT_CALL(*shoulder_servo_mock_ptr_, begin(shoulder_pin));
    EXPECT_CALL(*knee_servo_mock_ptr_, begin(knee_pin));
    two_axis_leg_->begin();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenBothServosArentFinishedAndInterpolationWillUpdateServos)
{
    set_max_height_and_forward_interpolation();

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, get_value())
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, get_value())
        .WillOnce(::testing::Return(2));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1));
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2));

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenOneServoIsntFinishedAndInterpolationWillUpdateServos)
{
    set_max_height_and_forward_interpolation();

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, get_value())
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, get_value())
        .WillOnce(::testing::Return(2));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1));
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2));

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenBothServosAreFinishedAndInterpolationWillNotUpdateServos)
{
    set_max_height_and_forward_interpolation();

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(::testing::_))
        .Times(0);
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(::testing::_))
        .Times(0);

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenBothServosArentFinishedAndSmoothWillUpdateServos)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, get_value())
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(*knee_smoother_mock_ptr_, get_value())
        .WillOnce(::testing::Return(2));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1));
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2));

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenOneServoIsntFinishedAndSmoothWillUpdateServos)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*knee_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false));

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, get_value())
        .WillOnce(::testing::Return(1));
    EXPECT_CALL(*knee_smoother_mock_ptr_, get_value())
        .WillOnce(::testing::Return(2));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(1));
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(2));

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenBothServosAreFinishedAndSmoothWillNotUpdateServos)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));
    EXPECT_CALL(*knee_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(true));

    EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(::testing::_))
        .Times(0);
    EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(::testing::_))
        .Times(0);

    two_axis_leg_->update_position();
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsFirstNewPositionAndInterpolationWillSetPosition)
{
    set_max_height_and_forward_interpolation();
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsSecondSamePositionAndInterpolationWillNotSetPositionTwice)
{
    set_max_height_and_forward_interpolation();

    two_axis_leg_->set_position(127, 127, movement::interpolation);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewHeightAndInterpolationWillSetPosition)
{
    set_max_height_and_forward_interpolation(2);

    EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(30, 40))
        .WillOnce(::testing::Return(75));
    EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(30, 40))
        .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
    EXPECT_CALL(*height_triangle_mock_, generate_angles(75))
        .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, start(
        ::testing::_,
        ::testing::_,
        ::testing::_,
        ::testing::Matcher<hal::interpolation_curve>(
            hal::interpolation_curve::SINUSOIDAL_OUT)));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, start(
        ::testing::_,
        ::testing::_,
        ::testing::_,
        ::testing::Matcher<hal::interpolation_curve>(
            hal::interpolation_curve::SINUSOIDAL_OUT)));

    two_axis_leg_->set_position(-128, 127, movement::interpolation);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewForwardBackAndInterpolationWillSetPosition)
{
    set_max_height_and_forward_interpolation(2);

    EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(-30, 95))
        .WillOnce(::testing::Return(75));
    EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(-30, 95))
        .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
    EXPECT_CALL(*height_triangle_mock_, generate_angles(75))
        .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, start(
        ::testing::_,
        ::testing::_,
        ::testing::_,
        ::testing::Matcher<hal::interpolation_curve>(
            hal::interpolation_curve::SINUSOIDAL_OUT)));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, start(
        ::testing::_,
        ::testing::_,
        ::testing::_,
        ::testing::Matcher<hal::interpolation_curve>(
            hal::interpolation_curve::SINUSOIDAL_OUT)));

    two_axis_leg_->set_position(127, -128, movement::interpolation);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsFirstNewPositionAndSmoothWillSetPosition)
{
    set_max_height_and_forward_smooth();
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsSecondSamePositionAndSmoothWillNotSetPositionTwice)
{
    set_max_height_and_forward_smooth();

    two_axis_leg_->set_position(127, 127, movement::smooth);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewHeightAndSmoothWillSetPosition)
{
    set_max_height_and_forward_smooth(2);

    EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(30, 40))
        .WillOnce(::testing::Return(75));
    EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(30, 40))
        .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
    EXPECT_CALL(*height_triangle_mock_, generate_angles(75))
        .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, start(
        ::testing::_,
        ::testing::_));
    EXPECT_CALL(*knee_smoother_mock_ptr_, start(
        ::testing::_,
        ::testing::_));

    two_axis_leg_->set_position(-128, 127, movement::smooth);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewForwardBackAndSmoothWillSetPosition)
{
    set_max_height_and_forward_smooth(2);

    EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(-30, 95))
        .WillOnce(::testing::Return(75));
    EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(-30, 95))
        .WillOnce(::testing::Return(std::make_tuple(10.0, 20.0, 30.0)));
    EXPECT_CALL(*height_triangle_mock_, generate_angles(75))
        .WillOnce(::testing::Return(std::make_tuple(40.0, 50.0, 60.0)));

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, start(
        ::testing::_,
        ::testing::_));
    EXPECT_CALL(*knee_smoother_mock_ptr_, start(
        ::testing::_,
        ::testing::_));

    two_axis_leg_->set_position(127, -128, movement::smooth);
}

}
