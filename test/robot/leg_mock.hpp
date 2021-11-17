#ifndef ROBOT_LEG_MOCK_HPP
#define ROBOT_LEG_MOCK_HPP

#include <gmock/gmock.h>
#include <robot/leg.hpp>

namespace robot
{

class leg_mock : public leg
{
public:
    MOCK_METHOD2(begin, void(uint8_t shoulder_pin, uint8_t knee_pin));

    MOCK_METHOD2(set_position, void(int8_t height, int8_t forward_back));

    MOCK_METHOD0(update_position, void());
};

}

#endif
