#ifndef HAL_CONFIG_MANAGER_HPP
#define HAL_CONFIG_MANAGER_HPP

#include "../../utility/config/robot_settings_fwd.hpp"

namespace hal
{
namespace config
{

class manager
{
public:
    virtual ~manager(){}

    virtual void begin() const = 0;

    virtual void save_settings(
        const utility::config::robot_settings& settings) = 0;

    virtual void get_settings(
        utility::config::robot_settings& settings) const = 0;
};

}
}

#endif
