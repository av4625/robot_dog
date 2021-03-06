#ifndef HAL_ROBOT_LEG_FACTORY_MOCK_HPP
#define HAL_ROBOT_LEG_FACTORY_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/robot/leg_factory.hpp>

namespace hal
{
namespace robot
{

class leg_factory_mock : public leg_factory
{
public:
    MOCK_METHOD(
        std::unique_ptr<::robot::leg>,
        create,
        (
            utility::robot::leg_type type,
            const std::shared_ptr<hal::hardware::arduino> arduino,
            const std::shared_ptr<const mathmatics::calculations> calculations,
            uint8_t shoulder_pin,
            uint8_t knee_pin
        ),
        (const, override));
};

}
}

#endif
