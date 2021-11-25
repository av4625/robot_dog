#ifndef ROBOT_LEG_MOCK_HPP
#define ROBOT_LEG_MOCK_HPP

#include <gmock/gmock.h>
#include <robot/leg.hpp>

namespace robot
{

class leg_mock : public leg
{
public:
    MOCK_METHOD0(begin, void());

    MOCK_METHOD3(set_position, void(int8_t height, int8_t forward_back, movement move_type));

    MOCK_METHOD0(update_position, void());
};

}

#endif
