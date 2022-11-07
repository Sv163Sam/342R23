cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
include_directories( "${CMAKE_SOURCE_DIR}" )
add_executable(untitled main.cpp u_pipe.h mes_queue.h signals.h check.h helper.h signals.cpp u_pipe.cpp mes_queue.cpp helper.cpp phum.cpp)

find_library(LIBRT rt REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lrt")
target_link_libraries(untitled ${LIBRT})