#include "dog.hpp"

namespace robot
{

dog::dog(
    std::unique_ptr<leg> front_left,
    std::unique_ptr<leg> front_right,
    std::unique_ptr<leg> back_left,
    std::unique_ptr<leg> back_right) :
        front_left_(std::move(front_left)),
        front_right_(std::move(front_right)),
        back_left_(std::move(back_left)),
        back_right_(std::move(back_right))
{
}

}
