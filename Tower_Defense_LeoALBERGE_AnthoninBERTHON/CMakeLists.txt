cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}" d)
if(NOT EXISTS "${d}")
    message(FATAL_ERROR "Error: environment variable IMAGINEPP_ROOT=" "${d}")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")
set(CMAKE_CXX_FLAGS "-std=c++11")
find_package(Imagine)

project(Tower_Defense_9)
add_executable(Tower_Defense_9
               main.cpp
               tour.h tour.cpp
               monstre.h monstre.cpp
               carte.h carte.cpp
               vague.h vague.cpp
               menu.h menu.cpp
               outils.h outils.cpp)
ImagineUseModules(Tower_Defense_9 Graphics)
