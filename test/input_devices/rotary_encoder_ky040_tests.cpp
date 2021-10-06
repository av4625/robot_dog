#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include <hal/hardware/arduino_mock.hpp>
#include <input_devices/rotary_encoder.hpp>

/**
 * Clockwise (clock,data): 0,1 -> 1,0 -> 0,1 -> 1,0
 * Anti Clockwise (clock,data): 1,1 -> 0,0 -> 1,1 -> 0,0
 *
 * Clockwise to Anti Clockwise: 0,1 –> 1,1 or 1,0 –> 0,0
 * Anti Clockwise to Clockwise: 1,1 –> 0,1 or 0,0 –> 1,0
 */

namespace input_devices
{

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Values;

namespace
{

const uint8_t clock_pin = 1;
const uint8_t data_pin = 2;
const uint8_t switch_pin = 3;

class RotaryEncoderKY040 : public ::testing::Test
{
protected:
    RotaryEncoderKY040()
        : arduino_mock_(
            std::make_shared<NiceMock<hal::hardware::arduino_mock> >()),
        ky040_(clock_pin, data_pin, switch_pin, arduino_mock_)
    {
    }

    void rotary_encoder_begin(const int clock_reading);

    // Using a NiceMock so that we don't need EXPECT_CALL's for Serial prints
    const std::shared_ptr<NiceMock<hal::hardware::arduino_mock> > arduino_mock_;
    rotary_encoder<rotary_encoder_type::ky040> ky040_;
};

void RotaryEncoderKY040::rotary_encoder_begin(const int clock_reading)
{
    EXPECT_CALL(*arduino_mock_, pin_mode(clock_pin, hal::hardware::input));
    EXPECT_CALL(*arduino_mock_, pin_mode(data_pin, hal::hardware::input));
    EXPECT_CALL(*arduino_mock_, pin_mode(
        switch_pin, hal::hardware::input_pullup));
    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(clock_reading));
    EXPECT_CALL(*arduino_mock_, digital_read(switch_pin)).WillOnce(Return(1));

    ky040_.begin();
}

}

TEST_F(RotaryEncoderKY040, BeginWillSetPinsAndGetInitialPinReadings)
{
    rotary_encoder_begin(0);
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenGapBetweenCurrentTimesIsLessThanOneWillNotRegisterSecondTurn)
{
    rotary_encoder_begin(0);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillOnce(Return(5));

    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::no_rotation, ky040_.check_rotary(5));
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenClockHasntChangedWillNotIncreasePosition)
{
    rotary_encoder_begin(0);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillOnce(Return(5));

    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::no_rotation, ky040_.check_rotary(7));
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenClockWiseThenAntiClockwiseWillReturnCorrectDirection)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .Times(2)
        .WillRepeatedly(Return(5));

    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::left, ky040_.check_rotary(7));
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenClockWiseThenAntiClockwiseDifferentStartWillReturnCorrectDirection)
{
    rotary_encoder_begin(0);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, millis())
        .Times(2)
        .WillRepeatedly(Return(5));

    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::left, ky040_.check_rotary(7));
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenAntiClockWiseThenClockwiseWillReturnCorrectDirection)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, millis())
        .Times(2)
        .WillRepeatedly(Return(5));

    EXPECT_EQ(rotation_direction::left, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(7));
}

TEST_F(RotaryEncoderKY040,
    CheckRotaryWhenAntiClockWiseThenClockwiseDifferentStartWillReturnCorrectDirection)
{
    rotary_encoder_begin(0);

    EXPECT_CALL(*arduino_mock_, digital_read(clock_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(0));

    EXPECT_CALL(*arduino_mock_, digital_read(data_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .Times(2)
        .WillRepeatedly(Return(5));

    EXPECT_EQ(rotation_direction::left, ky040_.check_rotary(4));
    EXPECT_EQ(rotation_direction::right, ky040_.check_rotary(7));
}

TEST_F(RotaryEncoderKY040,
    CheckButtonWhenGapBetweenCurrentTimesIsLessThanFiveWillNotRegisterSecondPress)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(switch_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillRepeatedly(Return(10));

    EXPECT_EQ(button_press_type::button_down, ky040_.check_button(10));
    EXPECT_EQ(button_press_type::button_press, ky040_.check_button(16));
    EXPECT_EQ(button_press_type::no_button_press, ky040_.check_button(15));
}

TEST_F(RotaryEncoderKY040,
    CheckButtonWhenPinStateDoesntChangeWillNotRegister)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(switch_pin))
        .WillOnce(Return(1))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillRepeatedly(Return(10));

    EXPECT_EQ(button_press_type::no_button_press, ky040_.check_button(10));
    EXPECT_EQ(button_press_type::no_button_press, ky040_.check_button(20));
}

TEST_F(RotaryEncoderKY040,
    CheckButtonWhenButtonLiftedWillRegisterAPress)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(switch_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillRepeatedly(Return(10));

    EXPECT_EQ(button_press_type::button_down, ky040_.check_button(10));
    EXPECT_EQ(button_press_type::button_press, ky040_.check_button(1510));
}

TEST_F(RotaryEncoderKY040,
    CheckButtonWhenLongPressWillResetCount)
{
    rotary_encoder_begin(1);

    EXPECT_CALL(*arduino_mock_, digital_read(switch_pin))
        .WillOnce(Return(0))
        .WillOnce(Return(1))
        .WillOnce(Return(0))
        .WillOnce(Return(1));

    EXPECT_CALL(*arduino_mock_, millis())
        .WillRepeatedly(Return(10));

    EXPECT_EQ(button_press_type::button_down, ky040_.check_button(10));
    EXPECT_EQ(button_press_type::button_press, ky040_.check_button(16));
    EXPECT_EQ(button_press_type::button_down, ky040_.check_button(20));
    EXPECT_EQ(button_press_type::long_button_press, ky040_.check_button(1511));
}

}
