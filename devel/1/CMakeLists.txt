
cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 14)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)


add_executable(first-scene ogre/example-1.cc)
target_link_libraries(first-scene OgreBites)

