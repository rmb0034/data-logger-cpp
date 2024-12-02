cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(DLog)

find_package(HDF5 REQUIRED COMPONENTS CXX)

include_directories(include)

add_library(DataLogger SHARED src/DataLogger.cpp)

target_include_directories(DataLogger PRIVATE ${HDF5_INCLUDE_DIRS})
target_link_libraries(DataLogger PRIVATE ${HDF5_LIBRARIES})

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE DataLogger)
target_include_directories(main PRIVATE ${HDF5_INCLUDE_DIRS})
