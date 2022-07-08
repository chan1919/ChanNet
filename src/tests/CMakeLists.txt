project(tests)

# util_test
add_executable(util_test util_test.cc)
target_link_libraries(util_test channet)
add_test(NAME util_test COMMAND util_test)

# InetAddress_test
add_executable(InetAddress_test InetAddress_test.cc)
target_link_libraries(InetAddress_test channet)
add_test(NAME InetAddress_test COMMAND InetAddress_test)
