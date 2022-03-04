add_library(controller
    ${SRC_DIR}/controller/context_impl.cpp
    ${SRC_DIR}/controller/controller.cpp
    ${SRC_DIR}/controller/handler_router.cpp
    ${SRC_DIR}/controller/state_base.cpp
    ${SRC_DIR}/controller/state_lean.cpp
    ${SRC_DIR}/controller/state_store_impl.cpp
    ${SRC_DIR}/controller/state_trim.cpp)

add_executable(controller_tests
    context_impl_tests.cpp
    controller_tests.cpp
    handler_router_tests.cpp
    state_lean_tests.cpp
    state_store_impl_tests.cpp
    state_trim_tests.cpp)

target_link_libraries(controller_tests PRIVATE
    controller unittests)

add_test(NAME controller_tests COMMAND controller_tests)
