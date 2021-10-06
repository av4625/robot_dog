add_library(trigonometry
    ${SRC_DIR}/mathmatics/trigonometry/isosceles_triangle_impl.cpp
    ${SRC_DIR}/mathmatics/trigonometry/right_angled_triangle_impl.cpp)

add_executable(trigonometry_tests
    isosceles_triangle_impl_tests.cpp
    right_angled_triangle_impl_tests.cpp)

target_link_libraries(trigonometry_tests PRIVATE
    trigonometry unittests)

add_test(NAME trigonometry_tests COMMAND trigonometry_tests)
