# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

idf_build_get_property(MODE MODE)
if(MODE STREQUAL "polling")
 FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/polling/*.*)
elseif(MODE STREQUAL "interrupt")
 FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/interrupt/*.*)
else()
 message(FATAL_ERROR "Selecciona el modo polling o interrupt en Platformio.")
endif()
idf_component_register(SRCS ${app_sources})
