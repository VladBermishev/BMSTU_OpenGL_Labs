cmake_minimum_required(VERSION 3.21)
project(GLLib)
add_library(GLLib INTERFACE)
target_include_directories(GLLib INTERFACE ./include)
add_subdirectory(glad)

