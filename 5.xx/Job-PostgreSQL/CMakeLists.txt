cmake_minimum_required(VERSION 3.10)
project(ClientManager)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

add_executable(client_manager main.cpp)
target_link_libraries(client_manager ${PQXX_LIBRARIES})
