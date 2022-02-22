#ifndef HAL_ROBOT_LEG_FACTORY_HPP
#define HAL_ROBOT_LEG_FACTORY_HPP

#include <memory>

#include "../hardware/arduino_fwd.hpp"

#include "../../mathmatics/calculations_fwd.hpp"
#include "../../robot/leg.hpp"
#include "../../utility/robot/leg_type.hpp"

namespace hal
{
namespace robot
{

class leg_factory
{
public:
    virtual ~leg_factory(){}
    virtual std::unique_ptr<::robot::leg> create(
        utility::robot::leg_type type,
        const std::shared_ptr<hal::hardware::arduino> arduino,
        const std::shared_ptr<const mathmatics::calculations> calculations,
        uint8_t shoulder_pin,
        uint8_t knee_pin) const = 0;
};

}
}

#endif
