cmake_minimum_required(VERSION 3.10)
project(ChanNet)

include_directories(include)
add_library(channet STATIC src/util.cc)
add_subdirectory(src/tests/)