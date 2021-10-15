cmake_minimum_required (VERSION 2.8)

set(CMAKE_C_COMPILE ${CC})
set(CMAKE_HOMEPAGE_URL_COMPILER_ENV_VAR "")
project(lvgl_prj LANGUAGES C)

add_subdirectory(src)
