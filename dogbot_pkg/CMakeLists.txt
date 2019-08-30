cmake_minimum_required(VERSION 3.5)

set(DOGBOT_VERSION 0.1)

project(dogbot_pkg VERSION ${DOGBOT_VERSION} LANGUAGES CXX)# DESCRIPTION "API for React AI DogBot firmware interaction"))

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
find_package(catkin REQUIRED)
FIND_PACKAGE ( Threads REQUIRED )

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(JSONCPP jsoncpp)
  pkg_check_modules(ZMQ libzmq)
  pkg_check_modules(LIBUSB libusb-1.0)
endif()

include_directories(${JSONCPP_INCLUDE_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

include_directories(${ZMQ_INCLUDE_DIRS})
link_directories(${ZMQ_LIBRARY_DIRS})

include_directories(${LIBUSB_INCLUDE_DIRS})
link_directories(${LIBUSB_LIBRARY_DIRS})


ADD_LIBRARY (DogBotAPI STATIC
        src/Coms.cc
        src/ComsZMQServer.cc
        src/ComsZMQClient.cc
        src/ComsSerial.cc
        src/ComsProxy.cc
        src/ComsUSB.cc
        src/ComsRecorder.cc
        src/ComsRoute.cc
        src/ComsVirtualDevice.cc
        src/DogBotAPI.cc
        src/Servo.cc
        src/LegKinematics.cc
        src/Joint.cc
        src/JointRelative.cc
        src/Joint4BarLinkage.cc
        src/ZMQContext.cc
        src/CallbackArray.cc
        src/FirmwareUpdate.cc
        src/Util.cc
        src/LegController.cc
        src/SplineCatmullRom.cc
        src/SimpleQuadrupedController.cc
        src/SplineGaitController.cc
        src/LineABC2d.cc
        src/Device.cc
        src/DeviceIMU.cc
        src/DogBotKinematics.cc
        src/PoseAngles.cc
        src/DogBotController.cc
        src/SimpleQuadrupedPose.cc
        src/DevicePlatformManager.cc
        src/PlatformManager.cc
        src/Strings.cc
)

set_target_properties(DogBotAPI PROPERTIES VERSION ${PROJECT_VERSION})

set_property(TARGET DogBotAPI PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries (DogBotAPI LINK_PUBLIC ${JSONCPP_LIBRARIES} ${ZMQ_LIBRARIES} ${LIBUSB_LIBRARIES})

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES dogbot_pkg
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)


add_executable (exampleClient src/exampleClient.cc)
target_link_libraries (exampleClient LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT} ${LIBUSB_LIBRARIES})

add_executable (dumpServoState src/dumpServoState.cc)
target_link_libraries (dumpServoState LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (testKinematics src/testKinematics.cc)
target_link_libraries (testKinematics LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (dogBotServer src/dogBotServer.cc)
target_link_libraries (dogBotServer LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (dogBotFirmwareUpdate src/dogBotFirmwareUpdate.cc)
target_link_libraries (dogBotFirmwareUpdate LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (dumpLegCoordinates src/dumpLegCoordinates.cc)
target_link_libraries (dumpLegCoordinates LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (dogBotExerciser src/dogBotExerciser.cc)
target_link_libraries (dogBotExerciser LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT})

add_executable (testDogBotGait src/testDogBotGait.cc)
target_link_libraries (testDogBotGait LINK_PUBLIC DogBotAPI )

add_executable (dogBotJig src/dogBotJig.cc)
target_link_libraries (dogBotJig LINK_PUBLIC DogBotAPI  ${CMAKE_THREAD_LIBS_INIT})

add_executable (dogBotWalk src/dogBotWalk.cc)
target_link_libraries (dogBotWalk LINK_PUBLIC DogBotAPI ${CMAKE_THREAD_LIBS_INIT} DogBotAPI)

install(DIRECTORY include/dogbot/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})
