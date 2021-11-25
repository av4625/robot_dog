add_subdirectory(trigonometry)

add_library(mathmatics
    ${SRC_DIR}/mathmatics/calculations.cpp
    ${SRC_DIR}/mathmatics/smoother_impl.cpp)

add_executable(mathmatics_tests calculations_tests.cpp smoother_impl_tests.cpp)

target_link_libraries(mathmatics_tests PRIVATE
    mathmatics unittests)

add_test(NAME mathmatics_tests COMMAND mathmatics_tests)
