#ifndef HAL_EXECUTER_HPP
#define HAL_EXECUTER_HPP

#include <functional>

namespace hal
{

class executer
{
public:
    virtual ~executer(){}

    virtual void execute(std::function<void()> func) const = 0;
};

}

#endif
