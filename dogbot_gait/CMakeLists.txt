cmake_minimum_required(VERSION 2.8.3)
project(dogbot_gait)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  control_msgs
  roscpp
  std_msgs
  pluginlib
  cmake_modules
  message_generation
)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(JSONCPP jsoncpp)
endif()

include_directories(${JSONCPP_INCLUDE_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()


## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

add_definitions(-std=c++11 -g)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{PROJECT_OUT}/lib/cmake")

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES dogbot_gait
  CATKIN_DEPENDS control_msgs  roscpp sensor_msgs std_msgs message_runtime roslib 
#  DEPENDS
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ library
add_library(dogbot_gait
   src/QuadrupedController.cc
   src/QuadrupedPose.cc
   src/SplineGaitController.cc
   src/Splines.cc
   src/DogBotV4LegKinematics.cc
   src/LineABC2d.cc
)

target_link_libraries(dogbot_gait  
  ${catkin_LIBRARIES}
  jsoncpp
)

## Declare a C++ executable
add_executable(dogbot_gait_node src/dogbot_gait_node.cc)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(dogbot_gait_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} dogbot_gait)

## Specify libraries to link a library or executable target against
target_link_libraries(dogbot_gait_node
  ${catkin_LIBRARIES}
  dogbot_gait
)

#############
## Install ##
#############

## Mark cpp header files for installation
 install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
   FILES_MATCHING PATTERN "*.h"
   PATTERN ".svn" EXCLUDE
 )

install(DIRECTORY meshes launch rviz urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
