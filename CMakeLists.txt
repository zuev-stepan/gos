cmake_minimum_required(VERSION 3.17)
project(gradient_finder)

set(CMAKE_CXX_STANDARD 17)

add_executable(gradient_finder main.cpp matrix.h gradient_description.h color.h column_accessor.h algorithm.h simple_algorithm.h rect.h)