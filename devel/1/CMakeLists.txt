
cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_STANDARD 14)

find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)


add_executable(example-1 ogre/example-1.cc)
target_link_libraries(example-1 OgreBites)


add_executable(example-2 ogre/example-2.cc)
target_link_libraries(example-2 OgreBites)

