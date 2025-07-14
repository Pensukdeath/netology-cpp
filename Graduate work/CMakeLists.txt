cmake_minimum_required(VERSION 3.20)

project(CppDiplomProject)

configure_file("Ini/config.ini"
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# TODO: Define by your own needs:
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")

set(BOOST_ROOT "d:/boost_1_86_0")

set(libpqxx_DIR "libpqxx-7.8.1")


# TODO: If you are running on Windows below 10, change this:

add_compile_definitions(_WIN32_WINNT=0x0A01)



# Boost:
find_package(Boost)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost")
endif()


# PQXX
set(PostgreSQL_ADDITIONAL_VERSIONS "17")

add_subdirectory(${libpqxx_DIR} libpqxx-build) 


# OpenSSL
find_package(OpenSSL REQUIRED)



add_subdirectory(Crawler)

add_subdirectory(Server)
