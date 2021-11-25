#ifndef MATHMATICS_SMOOTHER_MOCK_HPP
#define MATHMATICS_SMOOTHER_MOCK_HPP

#include <gmock/gmock.h>
#include <mathmatics/smoother.hpp>

namespace mathmatics
{

class smoother_mock : public smoother
{
public:
    MOCK_METHOD2(start, void(short start, short destination));
    MOCK_METHOD0(get_value, short());
    MOCK_CONST_METHOD0(is_finished, bool());
};

}

#endif
