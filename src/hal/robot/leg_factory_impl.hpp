#ifndef HAL_ROBOT_LEG_FACTORY_IMPL_HPP
#define HAL_ROBOT_LEG_FACTORY_IMPL_HPP

#include "leg_factory.hpp"

namespace hal
{
namespace robot
{

class leg_factory_impl : public leg_factory
{
public:
    std::unique_ptr<::robot::leg> create(
        ::robot::leg_type type,
        const std::shared_ptr<hal::hardware::arduino> arduino,
        const std::shared_ptr<const mathmatics::calculations> calculations,
        uint8_t shoulder_pin,
        uint8_t knee_pin) const override;
};

}
}

#endif
