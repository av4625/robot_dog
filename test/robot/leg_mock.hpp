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
        (int8_t height, int8_t forward_back, movement move_type),
        (override));

    MOCK_METHOD(void, update_position, (), (override));
};

}

#endif
