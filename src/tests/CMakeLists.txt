project(tests)

# util_test
add_executable(util_test util_test.cc)
target_link_libraries(util_test channet)
add_test(NAME util_test COMMAND util_test)

# InetAddress_test
add_executable(InetAddress_test InetAddress_test.cc)
target_link_libraries(InetAddress_test channet)
add_test(NAME InetAddress_test COMMAND InetAddress_test)

# # socket_test 存在问题
# add_executable(Socket_test Socket_test.cc)
# target_link_libraries(Socket_test channet pthread)
# add_test(NAME sock_test COMMAND Socket_test)

# Buffer_test
add_executable(Buffer_test Buffer_test.cc)
target_link_libraries(Buffer_test channet)
add_test(NAME Buffer_test COMMAND Buffer_test)

# ThreadPool_test
add_executable(ThreadPool_test ThreadPool_test.cc)
target_link_libraries(ThreadPool_test channet pthread)
add_test(NAME ThreadPool_test COMMAND ThreadPool_test)
