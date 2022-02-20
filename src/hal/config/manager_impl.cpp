#include "manager_impl.hpp"
#include "../../utility/config/robot_settings.hpp"

#include <EEPROM.h>

namespace hal
{
namespace config
{

void manager_impl::begin() const
{
    EEPROM.begin(sizeof(utility::config::robot_settings));
}

void manager_impl::save_settings(
    const utility::config::robot_settings& settings)
{
    EEPROM.put(0, settings);
    EEPROM.commit();
}

void manager_impl::get_settings(utility::config::robot_settings& settings) const
{
    EEPROM.get(0, settings);
}

}
}
