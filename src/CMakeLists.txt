cmake_minimum_required(VERSION 3.2)

set(MY_PROJECT_NAME "Traversing")
set(EXEC_NAME "main")
set(CMAKE_CXX_STANDARD 17)
project(${MY_PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(${EXEC_NAME} main.cc)
