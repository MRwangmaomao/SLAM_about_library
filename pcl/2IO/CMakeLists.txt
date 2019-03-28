cmake_minimum_required(VERSION 2.8.3)
project(IO_study)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)
# ����ѡ�� Debugģʽ
add_definitions("-Wall -g") 
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

link_directories("${CMAKE_CURRENT_SOURCE_DIR}/libLAS/lib")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libLAS/include")
# find the PCL package at minimum version 1.8. 
find_package(PCL 1.7 REQUIRED COMPONENTS common io)
# set to the paths to PCL installed headers and the dependency headers
include_directories(${PCL_INCLUDE_DIRS})
# set to the file names of the built and installed PCL libraries
link_directories(${PCL_LIBRARY_DIRS}) 
# lists the needed preprocessor definitions and compiler flags
add_definitions(${PCL_DEFINITIONS})

add_executable(pcd_read pcd_read.cpp)
target_link_libraries(pcd_read ${PCL_LIBRARIES})

add_executable(pcd_write pcd_write.cpp)
target_link_libraries(pcd_write ${PCL_LIBRARIES})

add_executable(concatenatingpcd concatenatingpcd.cpp)
target_link_libraries(concatenatingpcd ${PCL_LIBRARIES})
 
add_executable (ply2pcd ply2pcd.cpp)
target_link_libraries (ply2pcd ${PCL_LIBRARIES})
 