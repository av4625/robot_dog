#ifndef MATHMATICS_SMOOTHER_MOCK_HPP
#define MATHMATICS_SMOOTHER_MOCK_HPP

#include <gmock/gmock.h>
#include <mathmatics/smoother.hpp>

namespace mathmatics
{

class smoother_mock : public smoother
{
public:
    MOCK_METHOD(void, start, (short start, short destination), (override));
    MOCK_METHOD(short, get_value, (), (override));
    MOCK_METHOD(bool, is_finished, (), (const, override));
};

}

#endif
