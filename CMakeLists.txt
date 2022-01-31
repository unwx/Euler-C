cmake_minimum_required(VERSION 3.21)
project(Euler C)

set(CMAKE_C_STANDARD 23)

add_executable(Euler main.c random.c random.h euler67.c euler67.h euler83.c euler83.h timer.c timer.h array_utils.c array_utils.h)