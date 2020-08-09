cmake_minimum_required(VERSION 3.17)
project(Terminal_App_Launcher C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Terminal_App_Launcher main.c)
target_link_libraries(Terminal_App_Launcher ${CURSES_LIBRARIES})