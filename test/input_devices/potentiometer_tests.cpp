#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include <hal/hardware/arduino_mock.hpp>
#include <input_devices/potentiometer.hpp>

namespace input_devices
{

namespace
{

class PotentiometerTests : public ::testing::Test
{
protected:
    PotentiometerTests() :
        arduino_mock_(
            std::make_shared<hal::hardware::arduino_mock>()),
        pin_(10),
        pot_(arduino_mock_, pin_)
    {
    }

    const std::shared_ptr<hal::hardware::arduino_mock> arduino_mock_;
    const uint8_t pin_;
    potentiometer pot_;
};

}

TEST_F(PotentiometerTests, ReadWillCallAnalogRead)
{
    EXPECT_CALL(*arduino_mock_, analog_read(pin_))
        .WillOnce(::testing::Return(400));
    EXPECT_EQ(400, pot_.read());
}

}
