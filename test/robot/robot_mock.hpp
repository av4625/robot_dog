#ifndef ROBOT_ROBOT_MOCK_HPP
#define ROBOT_ROBOT_MOCK_HPP

#include <gmock/gmock.h>
#include <robot/robot.hpp>

namespace robot
{

class robot_mock : public robot
{
public:
    MOCK_METHOD(void, begin, (), (override));

    MOCK_METHOD(
        void, set_position, (int8_t height, int8_t forward_back), (override));

    MOCK_METHOD(void, set_height, (int8_t height), (override));

    MOCK_METHOD(void, set_forward_back, (int8_t forward_back), (override));

    MOCK_METHOD(bool, update_position, (), (override));

    MOCK_METHOD(void, fully_extend_legs, (), (override));

    MOCK_METHOD(void, set_legs_in_neutral_position, (), (override));

    MOCK_METHOD(
        void,
        trim_joint,
        (
            utility::robot::limb limb,
            utility::robot::joint joint,
            utility::robot::direction direction
        ),
        (override));
};

}

#endif
