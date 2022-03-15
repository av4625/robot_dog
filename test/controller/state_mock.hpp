#ifndef CONTROLLER_STATE_MOCK_HPP
#define CONTROLLER_STATE_MOCK_HPP

#include <gmock/gmock.h>
#include <controller/state.hpp>

namespace controller
{

class state_mock : public state
{
public:
    MOCK_METHOD(
        void,
        on_entry,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_exit,
        (const std::shared_ptr<context>& ctx),
        (const, override));

    MOCK_METHOD(std::string, get_name, (), (const, override));

    MOCK_METHOD(
        void,
        on_l_stick_y_move,
        (const std::shared_ptr<context>& ctx, int8_t y_location),
        (override));

    MOCK_METHOD(
        void,
        on_r_stick_y_move,
        (const std::shared_ptr<context>& ctx, int8_t x_location),
        (override));

    MOCK_METHOD(
        void,
        on_l2_move,
        (const std::shared_ptr<context>& ctx, uint8_t location),
        (override));

    MOCK_METHOD(
        void,
        on_r2_move,
        (const std::shared_ptr<context>& ctx, uint8_t location),
        (override));

    MOCK_METHOD(
        void,
        on_left_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_right_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_l1_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_r1_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_cross_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_circle_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        on_settings_button,
        (const std::shared_ptr<context>& ctx),
        (override));

    MOCK_METHOD(
        void,
        update,
        (const std::shared_ptr<context>& ctx),
        (override));
};

}

#endif
