add_subdirectory(trigonometry)

add_library(mathmatics ${SRC_DIR}/mathmatics/calculations.cpp)

add_executable(mathmatics_tests calculations_tests.cpp)

target_link_libraries(mathmatics_tests PRIVATE
    mathmatics unittests)

add_test(NAME mathmatics_tests COMMAND mathmatics_tests)
