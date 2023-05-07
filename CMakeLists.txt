cmake_minimum_required(VERSION 3.16)
project(dpkg_info)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(dpkg_info main.cpp)
target_link_libraries(dpkg_info fmt::fmt Boost::program_options)
