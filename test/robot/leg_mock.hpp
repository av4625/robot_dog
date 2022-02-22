#ifndef ROBOT_LEG_MOCK_HPP
#define ROBOT_LEG_MOCK_HPP

#include <gmock/gmock.h>
#include <robot/leg.hpp>

namespace robot
{

class leg_mock : public leg
{
public:
    MOCK_METHOD(void, begin, (), (override));

    MOCK_METHOD(
        void,
        set_position,
        (
            int8_t height,
            int8_t forward_back,
            utility::robot::movement move_type
        ),
        (override));

    MOCK_METHOD(
        void,
        set_height,
        (int8_t height, utility::robot::movement move_type),
        (override));

    MOCK_METHOD(
        void,
        set_forward_back,
        (int8_t forward_back, utility::robot::movement move_type),
        (override));

    MOCK_METHOD(bool, update_position, (), (override));

    MOCK_METHOD(void, set_leg_straight_down, (), (override));

    MOCK_METHOD(void, set_leg_neutral_position, (), (override));

    MOCK_METHOD(
        void,
        trim_joint,
        (
            utility::robot::joint joint,
            utility::robot::direction direction
        ),
        (override));
};

}

#endif
