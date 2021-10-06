add_library(input_devices
    ${SRC_DIR}/input_devices/potentiometer.cpp
    ${SRC_DIR}/input_devices/rotary_encoder.cpp)

target_link_libraries(input_devices PRIVATE defines)

add_executable(input_devices_tests
    potentiometer_tests.cpp
    rotary_encoder_ec11_tests.cpp
    rotary_encoder_ky040_tests.cpp)

target_link_libraries(input_devices_tests PRIVATE
    input_devices unittests)

add_test(NAME input_devices_tests COMMAND input_devices_tests)
