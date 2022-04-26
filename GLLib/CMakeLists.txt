cmake_minimum_required(VERSION 3.21)
project(GLLib)
add_library(GLLib INTERFACE)
target_include_directories(GLLib INTERFACE ./include)
add_subdirectory(glad)
target_link_libraries(GLLib INTERFACE glad  INTERFACE Freetype::Freetype ${CMAKE_DL_LIBS})

