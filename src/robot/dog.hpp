#ifndef ROBOT_DOG_HPP
#define ROBOT_DOG_HPP

#include "robot.hpp"

#include <memory>

#include "leg.hpp"

namespace robot
{

class dog : public robot
{
public:
    dog(
        std::unique_ptr<leg> front_left,
        std::unique_ptr<leg> front_right,
        std::unique_ptr<leg> back_left,
        std::unique_ptr<leg> back_right);

private:
    const std::unique_ptr<leg> front_left_;
    const std::unique_ptr<leg> front_right_;
    const std::unique_ptr<leg> back_left_;
    const std::unique_ptr<leg> back_right_;
};

}

#endif
