#ifndef HAL_CONFIG_MANAGER_IMPL_HPP
#define HAL_CONFIG_MANAGER_IMPL_HPP

#include "manager.hpp"

namespace hal
{
namespace config
{

class manager_impl : public manager
{
public:
    void begin() const;

    void save_settings(const utility::config::robot_settings& settings);

    void get_settings(utility::config::robot_settings& settings) const;
};

}
}

#endif
