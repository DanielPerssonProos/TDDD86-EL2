cmake_minimum_required(VERSION 3.3)
project(ExtraLab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES encrypt.cpp decrypt.cpp)
add_executable(ExtraLab2 ${SOURCE_FILES})