INCLUDE(FindPkgConfig)

pkg_check_modules(PKGS_DEP REQUIRED 
	wayland-client
	xkbcommon
)

FOREACH(flag ${PKGS_DEP_CFLAGS})
	set(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_C_FLAGS_DEBUG "${CFLAGS} ${EXTRA_FLAGS} ")
SET(CMAKE_C_FLAGS_RELEASE "${CFLAGS} ${EXTRA_FLAGS}")


#aux_source_directory(. DIR_SRCS)
#add_subdirectory(lvgl)
#add_subdirectory(lv_drivers)
#add_subdirectory(lv_demos)
include_directories(.)
include_directories(./lvgl/)
include_directories(./lv_drivers/)
include_directories(./lv_demos/src/lv_demo_music/)
include_directories(./lv_demos/src/lv_demo_widgets/)
include_directories(./lv_demos/src/lv_demo_benchmark/)

aux_source_directory(. DIR_SRCS)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)
add_subdirectory(lv_demos)

add_executable(lvgl_prj  ${DIR_SRCS})

set(VAR lv_examples)
set(VAR ${VAR} lvgl)
set(VAR ${VAR} lv_drivers)

message("VAR : ${VAR}")

target_link_libraries(lvgl_prj ${VAR})
target_link_libraries(lvgl_prj "-lpthread")
target_link_libraries(lvgl_prj ${PKGS_DEP_LDFLAGS})

