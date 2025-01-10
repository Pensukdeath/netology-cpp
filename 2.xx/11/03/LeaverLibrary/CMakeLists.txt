cmake_minimum_required(VERSION 3.22)

project(LeaverLibrary)

add_library(LeaverLibrary SHARED Leaver.cpp Leaver.h)

add_executable(LeaverPG main.cpp)

target_link_libraries(LeaverPG LeaverLibrary)

target_compile_definitions(LeaverLibrary PRIVATE LEAVERLIBRARY_EXPORTS)