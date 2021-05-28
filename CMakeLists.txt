cmake_minimum_required(VERSION 3.19)
project(esh VERSION 0.1)

set(CMAKE_CPP_STANDARD 11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c" "src/*.cpp")
add_executable(esh ${SOURCES})
target_include_directories(esh PUBLIC "${PROJECT_SOURCE_DIR}/inc")
target_link_libraries(esh readline)