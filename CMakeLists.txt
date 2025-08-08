cmake_minimum_required(VERSION 3.10)
project(2048Game)
set(CMAKE_CXX_STANDARD 17)

add_executable(2048Game main.cpp Game.cpp
        public_func.h
        public_func.cpp
        public_def.h
        public_def.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})