project(tests)
add_executable(util_test util_test.cc)
target_link_libraries(util_test channet)
add_test(NAME util_test COMMAND util_test)