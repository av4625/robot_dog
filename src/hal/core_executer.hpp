#ifndef HAL_CORE_EXECUTER_HPP
#define HAL_CORE_EXECUTER_HPP

#include "executer.hpp"

namespace hal
{

class core_executer : public executer
{
public:
    void execute(std::function<void()> func) const override;

private:
    static void executable(void* data);
};

}

#endif
