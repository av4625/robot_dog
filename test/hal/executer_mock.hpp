#ifndef HAL_EXECUTER_MOCK_HPP
#define HAL_EXECUTER_MOCK_HPP

#include <gmock/gmock.h>
#include <hal/executer.hpp>

namespace hal
{

class executer_mock : public executer
{
public:
    MOCK_METHOD(
        void, execute, (std::function<void()> func), (const, override));
};

}

#endif
