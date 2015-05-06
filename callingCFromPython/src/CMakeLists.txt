cmake_minimum_required(VERSION 2.8)

set(CMAKE_MACOSX_RPATH 1)


include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS "-Wall -Wextra -std=c11 -pedantic -fPIC")

add_library(square SHARED square.c)

install(TARGETS square
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    COMPONENT Devel)
