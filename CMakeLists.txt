cmake_minimum_required(VERSION 3.10)
project(ED2018s1_TPFinal_C1_Sarappa_Carla)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES
        ./*.h
        ./*.cpp
        )

add_executable(ED2018s1_TPFinal_C1_Sarappa_Carla ${SOURCES})
