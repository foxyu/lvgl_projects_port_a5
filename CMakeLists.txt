cmake_minimum_required (VERSION 2.8)

set(CMAKE_C_COMPILE ${CC})

set(CMAKE_INSTALL_PREFIX "./install/")

project(lvgl_prj)

add_subdirectory(src)
