cmake_minimum_required(VERSION 3.1)
project(ramiv1)

set (CMAKE_C_COMPILER gcc)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -g -std=c++14 -Wall -Wextra -pedantic")#



# source
file(GLOB SRC
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"    )

# ---------- EXECUTABLES -----------
#console
add_executable(console ${SRC} src/main.cpp)

# viewer
#set(VIEWER_NAME viewer) # nom de l'executable
#find_package(Qt5 COMPONENTS Core Quick REQUIRED) # find Qt
#set(CMAKE_AUTOMOC ON)