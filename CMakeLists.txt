cmake_minimum_required(VERSION 3.15)

project(Kostull VERSION 1.0)

add_subdirectory("Source")
add_subdirectory(Modules)
add_subdirectory(Vendor)

add_executable(Kostull "Source/main.cpp")

target_link_libraries(Kostull PRIVATE Logger Networking Graphics)