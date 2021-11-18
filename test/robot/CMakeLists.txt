add_library(robot ${SRC_DIR}/robot/dog.cpp ${SRC_DIR}/robot/two_axis_leg.cpp)

add_executable(robot_tests dog_tests.cpp two_axis_leg_tests.cpp)

target_link_libraries(robot_tests PRIVATE robot unittests)

add_test(NAME robot_tests COMMAND robot_tests)
