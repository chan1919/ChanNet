cmake_minimum_required(VERSION 3.10)
project(ChanNet)

#头文件目录
include_directories(include)

#定义源文件搜索处
aux_source_directory(src/ SRC)
#生成动态链接库 [供tests子模块使用]
add_library(channet SHARED ${SRC})
enable_testing()    
add_subdirectory(src/tests/)

