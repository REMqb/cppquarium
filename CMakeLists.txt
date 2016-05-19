project(cppquarium)
cmake_minimum_required(VERSION 3.1)

# set compiler / linker conf
set (CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE SRC_LIST src/*.*pp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
