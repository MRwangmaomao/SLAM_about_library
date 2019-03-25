cmake_minimum_required(VERSION 2.8.3)
project(eigen_study)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
# 编译选项 Debug模式
add_definitions("-Wall -g") 
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
  
# find the PCL package at minimum version 1.8. 
find_package(PCL 1.8 REQUIRED COMPONENTS common io)
# set to the paths to PCL installed headers and the dependency headers
include_directories(${PCL_INCLUDE_DIRS})
# set to the file names of the built and installed PCL libraries
link_directories(${PCL_LIBRARY_DIRS}) 
# lists the needed preprocessor definitions and compiler flags
add_definitions(${PCL_DEFINITIONS})

add_executable(BasicStructure BasicStructure.cpp)

target_link_libraries(BasicStructure ${PCL_LIBRARIES})

 
  
 