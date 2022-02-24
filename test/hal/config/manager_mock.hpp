#ifndef HAL_CONFIG_MANAGER_MOCK_HPP
#define HAL_CONFIG_MANAGER_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/config/manager.hpp>

namespace hal
{
namespace config
{

class manager_mock : public manager
{
public:
    MOCK_METHOD(void, begin, (), (const, override));

    MOCK_METHOD(
        void,
        save_settings,
        (const utility::config::robot_settings& settings),
        (override));

    MOCK_METHOD(
        void,
        get_settings,
        (utility::config::robot_settings& settings),
        (const, override));
};

}
}

#endif
