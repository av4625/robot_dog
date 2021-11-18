#include <gtest/gtest.h>

#include <memory>
#include <vector>

#include <robot/two_axis_leg.hpp>

#include <hal/hardware/servo_mock.hpp>
#include <hal/interpolation_mock.hpp>
#include <mathmatics/trigonometry/isosceles_triangle_mock.hpp>
#include <mathmatics/trigonometry/right_angled_triangle_mock.hpp>

namespace robot
{

namespace
{

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
        two_axis_leg_(
            forward_back_triangle_mock_,
            height_triangle_mock_,
            std::move(shoulder_servo_mock_),
            std::move(knee_servo_mock_),
            std::move(shoulder_interpolation_mock_),
            std::move(knee_interpolation_mock_),
            std::make_shared<const mathmatics::calculations>())
    {
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
    two_axis_leg two_axis_leg_;
};

}

}
