project(cppquarium.html)
cmake_minimum_required(VERSION 3.1)

# set compiler / linker conf
set (CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC_LIST src/*.*pp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fvisibility=hidden -fvisibility-inlines-hidden -std=c++1z")

add_executable(${PROJECT_NAME} ${SRC_LIST})
