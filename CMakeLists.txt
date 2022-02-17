cmake_minimum_required(VERSION 3.16)

project(LuaBenchmark)

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(PC_LUAJIT QUIET luajit)
endif()

find_path(LUAJIT_INCLUDE_DIR luajit.h
          PATHS ${PC_LUAJIT_INCLUDEDIR} ${PC_LUAJIT_INCLUDE_DIRS}
          PATH_SUFFIXES luajit-2.0 luajit-2.1)

list(APPEND LUAJIT_NAMES luajit-5.1)

find_library(LUAJIT_LIBRARY NAMES ${LUAJIT_NAMES}
             PATHS ${PC_LUAJIT_LIBDIR} ${PC_LUAJIT_LIBRARY_DIRS})


set(LUAJIT_LIBRARIES ${LUAJIT_LIBRARY})
set(LUAJIT_INCLUDE_DIRS ${LUAJIT_INCLUDE_DIR})

include_directories(
        sol2/include
        LuaBridge3/Source
        ${LUAJIT_INCLUDE_DIRS}
)

add_executable(sol_benchmark
        sol_main.cpp
        )
add_executable(luabridge_benchmark
        luabridge_main.cpp
        )

target_link_libraries(sol_benchmark ${LUAJIT_LIBRARIES})
target_link_libraries(luabridge_benchmark ${LUAJIT_LIBRARIES})

file(COPY ${PROJECT_SOURCE_DIR}/LuaScripts DESTINATION ${CMAKE_BINARY_DIR})
