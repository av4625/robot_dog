#include <gtest/gtest.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

#include <robot/two_axis_leg.hpp>

#include <hal/hardware/servo_mock.hpp>
#include <hal/interpolation_mock.hpp>
#include <mathmatics/calculations_impl.hpp>
#include <mathmatics/calculations_mock.hpp>
#include <mathmatics/smoother_mock.hpp>
#include <mathmatics/trigonometry/isosceles_triangle_mock.hpp>
#include <mathmatics/trigonometry/right_angled_triangle_mock.hpp>

namespace robot
{

namespace
{

const uint8_t shoulder_pin{1};
const uint8_t knee_pin{1};
const uint8_t min_height{40};
const uint8_t max_height{95};
const int8_t max_forward{-30};
const int8_t max_back{30};
const int8_t int8_min{-128};
const int8_t int8_max{127};
const short starting_microseconds{1500};
const double zero_degrees_radians{0};
const double forty_five_degrees_radians{M_PI / 4};
const double ninety_degrees_radians{M_PI / 2};
const double one_hundred_and_thirty_five_degrees_radians{
    M_PI - forty_five_degrees_radians};
const double one_hundred_and_eighty_degrees_radians{M_PI};
const short starting_shoulder_trim{40};
const short starting_knee_trim{100};
const short min_servo_microseconds{500};
const short max_servo_microseconds{2500};
const short min_servo_microseconds_shoulder{
    min_servo_microseconds + starting_shoulder_trim};
const short max_servo_microseconds_shoulder{
    max_servo_microseconds + starting_shoulder_trim};
const short min_servo_microseconds_knee{
    min_servo_microseconds + starting_knee_trim};
const short max_servo_microseconds_knee{
    max_servo_microseconds + starting_knee_trim};

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
            knee_smoother_mock_.get())),
        calc_mock_(std::make_shared<const mathmatics::calculations_mock>())
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
            calc_mock_,
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
    const std::shared_ptr<const mathmatics::calculations_mock> calc_mock_;
    std::unique_ptr<leg> two_axis_leg_;

    void set_calculations_servo_expectations(
        const short shoulder_microseconds_ret,
        const short knee_microseconds_ret,
        const float shoulder_angle = 10 + 40,
        const float knee_angle = 60)
    {
        EXPECT_CALL(*calc_mock_, map(
            shoulder_angle,
            -forty_five_degrees_radians,
            one_hundred_and_thirty_five_degrees_radians,
            min_servo_microseconds_shoulder,
            max_servo_microseconds_shoulder
        )).WillOnce(::testing::Return(shoulder_microseconds_ret));

        EXPECT_CALL(*calc_mock_, map(
            knee_angle,
            zero_degrees_radians,
            one_hundred_and_eighty_degrees_radians,
            max_servo_microseconds_knee,
            min_servo_microseconds_knee
        )).WillOnce(::testing::Return(knee_microseconds_ret));

        EXPECT_CALL(*calc_mock_, constrict(
            ::testing::TypedEq<short>(shoulder_microseconds_ret),
            ::testing::TypedEq<short>(min_servo_microseconds),
            ::testing::TypedEq<short>(max_servo_microseconds)))
                .WillOnce(::testing::Return(shoulder_microseconds_ret));

        EXPECT_CALL(*calc_mock_, constrict(
            ::testing::TypedEq<short>(knee_microseconds_ret),
            ::testing::TypedEq<short>(min_servo_microseconds),
            ::testing::TypedEq<short>(max_servo_microseconds)))
                .WillOnce(::testing::Return(knee_microseconds_ret));
    }

    void set_calculations_triangle_expectations(
        const int8_t height,
        const int8_t forward_back,
        const uint8_t height_ret,
        const uint8_t forward_back_ret,
        const short shoulder_microseconds_ret,
        const short knee_microseconds_ret)
    {
        EXPECT_CALL(*calc_mock_, map(
            height,
            int8_min,
            int8_max,
            min_height,
            max_height
        )).WillOnce(::testing::Return(height_ret));

        EXPECT_CALL(*calc_mock_, map(
            forward_back,
            int8_min,
            int8_max,
            max_forward,
            max_back
        )).WillOnce(::testing::Return(forward_back_ret));

        set_calculations_servo_expectations(
            shoulder_microseconds_ret, knee_microseconds_ret);
    }

    void set_write_microseconds_expectations(
        const short shoulder = 1, const short knee = 2, const short times = 1)
    {
        EXPECT_CALL(*shoulder_servo_mock_ptr_, write_microseconds(shoulder))
            .Times(times);
        EXPECT_CALL(*knee_servo_mock_ptr_, write_microseconds(knee))
            .Times(times);
    }

    void set_triangle_expectations(
        const float forward_back,
        const float height,
        const float hypotenuse,
        const std::tuple<double, double, double>& forward_back_angles,
        const std::tuple<double, double, double>& height_angles)
    {
        EXPECT_CALL(*forward_back_triangle_mock_, calculate_hypotenuse(
            forward_back, height))
                .WillOnce(::testing::Return(hypotenuse));
        EXPECT_CALL(*forward_back_triangle_mock_, generate_angles(
            forward_back, height))
                .WillOnce(::testing::Return(forward_back_angles));
        EXPECT_CALL(*height_triangle_mock_, generate_angles(hypotenuse))
            .WillOnce(::testing::Return(height_angles));
    }

    void set_position_common_exceptions(const int times)
    {
        set_triangle_expectations(
            max_back,
            max_height,
            100,
            std::make_tuple(10.0, 20.0, 30.0),
            std::make_tuple(40.0, 50.0, 60.0));

        set_write_microseconds_expectations(1, 2, times);
    }

    void set_interpolation_start_expectations(
        const short shoulder_start = 1,
        const short shoulder_destination = 1000,
        const short knee_start = 2,
        const short knee_destination = 2000)
    {
        EXPECT_CALL(*shoulder_interpolation_mock_ptr_, start(
            shoulder_start,
            shoulder_destination,
            ::testing::_,
            ::testing::Matcher<hal::interpolation_curve>(
                hal::interpolation_curve::SINUSOIDAL_OUT)));
        EXPECT_CALL(*knee_interpolation_mock_ptr_, start(
            knee_start,
            knee_destination,
            ::testing::_,
            ::testing::Matcher<hal::interpolation_curve>(
                hal::interpolation_curve::SINUSOIDAL_OUT)));
    }

    void set_interpolation_get_value_expectations(
        const short shoulder = 1, const short knee = 2, const short times = 1)
    {
        EXPECT_CALL(*shoulder_interpolation_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(shoulder));
        EXPECT_CALL(*knee_interpolation_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(knee));
    }

    void set_max_height_and_forward_interpolation(const int times = 1)
    {
        set_position_common_exceptions(times);

        const int8_t height{127};
        const int8_t forward_back{127};

        set_calculations_triangle_expectations(
            height,
            forward_back,
            max_height,
            max_back,
            1000,
            2000);

        set_interpolation_start_expectations(
            starting_microseconds,
            1000,
            starting_microseconds,
            2000);

        set_interpolation_get_value_expectations(1, 2, times);

        two_axis_leg_->set_position(
            height, forward_back, utility::robot::movement::interpolation);
    }

    void set_smoother_start_expectations(
        const short shoulder_start = 1,
        const short shoulder_destination = 1000,
        const short knee_start = 2,
        const short knee_destination = 2000)
    {
        EXPECT_CALL(*shoulder_smoother_mock_ptr_, start(
            shoulder_start,
            shoulder_destination));
        EXPECT_CALL(*knee_smoother_mock_ptr_, start(
            knee_start,
            knee_destination));
    }

    void set_smoother_get_value_expectations(
        const short shoulder = 1, const short knee = 2, const short times = 1)
    {
        EXPECT_CALL(*shoulder_smoother_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(shoulder));
        EXPECT_CALL(*knee_smoother_mock_ptr_, get_value())
            .Times(times).WillRepeatedly(::testing::Return(knee));
    }

    void set_max_height_and_forward_smooth(const int times = 1)
    {
        set_position_common_exceptions(times);

        const int8_t height{127};
        const int8_t forward_back{127};

        set_calculations_triangle_expectations(
            height,
            forward_back,
            max_height,
            max_back,
            1000,
            2000);

        set_smoother_start_expectations(
            starting_microseconds, 1000, starting_microseconds, 2000);

        set_smoother_get_value_expectations(1, 2, times);

        two_axis_leg_->set_position(
            height, forward_back, utility::robot::movement::smooth);
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
        .Times(2).WillRepeatedly(::testing::Return(false));

    set_interpolation_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_FALSE(two_axis_leg_->update_position());
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenOneServoIsntFinishedAndInterpolationWillUpdateServos)
{
    set_max_height_and_forward_interpolation();

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(false));

    set_interpolation_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_FALSE(two_axis_leg_->update_position());
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenLastUpdateAndInterpolationWillUpdateServosAndReturnTrue)
{
    set_max_height_and_forward_interpolation();

    EXPECT_CALL(*shoulder_interpolation_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*knee_interpolation_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));

    set_interpolation_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_TRUE(two_axis_leg_->update_position());
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

    EXPECT_TRUE(two_axis_leg_->update_position());
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenBothServosArentFinishedAndSmoothWillUpdateServos)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(false));

    set_smoother_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_FALSE(two_axis_leg_->update_position());
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenOneServoIsntFinishedAndSmoothWillUpdateServos)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*knee_smoother_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(false));

    set_smoother_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_FALSE(two_axis_leg_->update_position());
}

TEST_F(TwoAxisLegTests,
    UpdatePositionWhenLastUpdateAndSmoothWillUpdateServosAndReturnTrue)
{
    set_max_height_and_forward_smooth();

    EXPECT_CALL(*shoulder_smoother_mock_ptr_, is_finished())
        .Times(2).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*knee_smoother_mock_ptr_, is_finished())
        .WillOnce(::testing::Return(false))
        .WillOnce(::testing::Return(true));

    set_smoother_get_value_expectations();

    set_write_microseconds_expectations();

    EXPECT_TRUE(two_axis_leg_->update_position());
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

    EXPECT_TRUE(two_axis_leg_->update_position());
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

    two_axis_leg_->set_position(
        127, 127, utility::robot::movement::interpolation);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewHeightAndInterpolationWillSetPosition)
{
    set_max_height_and_forward_interpolation(2);

    const int8_t height{-128};
    const int8_t forward_back{127};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        min_height,
        max_back,
        1000,
        2000);

    set_triangle_expectations(
        max_back,
        min_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_interpolation_start_expectations();

    two_axis_leg_->set_position(
        height, forward_back, utility::robot::movement::interpolation);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewForwardBackAndInterpolationWillSetPosition)
{
    set_max_height_and_forward_interpolation(2);

    const int8_t height{127};
    const int8_t forward_back{-128};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        max_height,
        max_forward,
        1000,
        2000);

    set_triangle_expectations(
        max_forward,
        max_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_interpolation_start_expectations();

    two_axis_leg_->set_position(
        height, forward_back, utility::robot::movement::interpolation);
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

    two_axis_leg_->set_position(127, 127, utility::robot::movement::smooth);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewHeightAndSmoothWillSetPosition)
{
    set_max_height_and_forward_smooth(2);

    const int8_t height{-128};
    const int8_t forward_back{127};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        min_height,
        max_back,
        1000,
        2000);

    set_triangle_expectations(
        max_back,
        min_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_smoother_start_expectations();

    two_axis_leg_->set_position(
        height, forward_back, utility::robot::movement::smooth);
}

TEST_F(TwoAxisLegTests,
    SetPositionWhenItsNewForwardBackAndSmoothWillSetPosition)
{
    set_max_height_and_forward_smooth(2);

    const int8_t height{127};
    const int8_t forward_back{-128};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        max_height,
        max_forward,
        1000,
        2000);

    set_triangle_expectations(
        max_forward,
        max_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_smoother_start_expectations();

    two_axis_leg_->set_position(
        height, forward_back, utility::robot::movement::smooth);
}

TEST_F(TwoAxisLegTests, SetHeightWillUsePreviousForwardBack)
{
    set_max_height_and_forward_smooth(2);

    const int8_t height{-128};
    const int8_t forward_back{127};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        min_height,
        max_back,
        1000,
        2000);

    set_triangle_expectations(
        max_back,
        min_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_smoother_start_expectations();

    two_axis_leg_->set_height(height, utility::robot::movement::smooth);
}

TEST_F(TwoAxisLegTests, SetForwardBackWillUsePreviousHeight)
{
    set_max_height_and_forward_smooth(2);

    const int8_t height{127};
    const int8_t forward_back{-128};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        max_height,
        max_forward,
        1000,
        2000);

    set_triangle_expectations(
        max_forward,
        max_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_smoother_start_expectations();

    two_axis_leg_->set_forward_back(
        forward_back, utility::robot::movement::smooth);
}

TEST_F(TwoAxisLegTests, SetLegStraightDownWillFullyExtendLeg)
{
    set_calculations_servo_expectations(2000, 2001, 0, 0);

    set_smoother_start_expectations(
        starting_microseconds, 2000, starting_microseconds, 2001);

    set_smoother_get_value_expectations();

    set_write_microseconds_expectations();

    two_axis_leg_->set_leg_straight_down();
}

TEST_F(TwoAxisLegTests, SetLegNeutralPositionWillSetMiddleHeight)
{
    // Set it to something other than the starting neutral so that calling
    // neutral looks like a new position
   set_max_height_and_forward_smooth(2);

    const int8_t height{0};
    const int8_t forward_back{0};
    const uint8_t middle_forward_back{0};
    const uint8_t middle_height{0};

    set_calculations_triangle_expectations(
        height,
        forward_back,
        middle_height,
        middle_forward_back,
        1000,
        2000);

    set_triangle_expectations(
        middle_forward_back,
        middle_height,
        75,
        std::make_tuple(10.0, 20.0, 30.0),
        std::make_tuple(40.0, 50.0, 60.0));

    set_smoother_start_expectations();

    two_axis_leg_->set_leg_neutral_position();
}

}
