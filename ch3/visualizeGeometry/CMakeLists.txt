cmake_minimum_required( VERSION 2.8 )
project( visualizeGeometry )

set(CMAKE_CXX_FLAGS "-std=c++11")

# 添加Eigen头文件:在mac中编译用第一个，在linux中编译用第二个
include_directories("/usr/local/Cellar/eigen/3.3.7/include/eigen3")
#include_directories( "/usr/include/eigen3" )

# 添加Pangolin依赖
find_package( Pangolin )
include_directories( ${Pangolin_INCLUDE_DIRS} )

add_executable( visualizeGeometry visualizeGeometry.cpp )
target_link_libraries( visualizeGeometry ${Pangolin_LIBRARIES} )
