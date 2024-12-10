cmake_minimum_required(VERSION 3.20)

# Название проекта
project(my_first_cmake_project)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Добавляем исходные файлы проекта
add_executable(my_first_cmake_program src/main.cpp)