cmake_minimum_required(VERSION 3.26)
project(GwintSerwer)

set(CMAKE_CXX_STANDARD 17)

add_executable(GwintSerwer main.cpp)
target_compile_options(GwintSerwer PRIVATE -Wall)
target_link_options(GwintSerwer PRIVATE -pthread)