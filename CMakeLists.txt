cmake_minimum_required(VERSION 3.10)
project(2048Game)
set(CMAKE_CXX_STANDARD 11)

add_executable(2048Game main.cpp Game.cpp
        public_func.h
        public_def.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})