cmake_minimum_required(VERSION 3.27)
project(FishMain)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FishMain
        Fish.cpp
        Fish.h
        FishMain.ino)
