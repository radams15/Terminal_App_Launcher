cmake_minimum_required(VERSION 3.10)
project(launcher C)

set(CMAKE_C_STANDARD 99)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} ${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(launcher main.c)
target_link_libraries(launcher ${CURSES_LIBRARIES} ${GTK3_LIBRARIES} m)

install(
        TARGETS launcher
        RUNTIME DESTINATION /usr/local/bin
)