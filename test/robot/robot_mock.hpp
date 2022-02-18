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
};

}

#endif
