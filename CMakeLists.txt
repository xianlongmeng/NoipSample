cmake_minimum_required(VERSION 3.25)
project(NoipSample)

set(CMAKE_CXX_STANDARD 23)

ADD_SUBDIRECTORY(UVA_Home)

add_executable(NoipSample main.cpp UVA_Home/helloworld.cpp)
