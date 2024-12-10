cmake_minimum_required(VERSION 3.20)

# Название проекта
project(Class_hierarchy_project)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Добавляем исходные файлы проекта
add_executable(Class_hierarchy_project Class_hierarchy.cpp EquilateralTriangle.cpp EquilateralTriangle.h InvalidShapeException.h IsoscelesTriangle.cpp IsoscelesTriangle.h Parallelogram.cpp Parallelogram.h Quadrilateral.cpp Quadrilateral.h Rectangle.cpp Rectangle.h Rhombus.cpp Rhombus.h RightTriangle.cpp RightTriangle.h Square.cpp Square.h Triangle.cpp Triangle.h)