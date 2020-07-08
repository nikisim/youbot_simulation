cmake_minimum_required(VERSION 2.8.3)
project(youbot_gazebo_control)

find_package(catkin REQUIRED
  COMPONENTS
    angles
    control_toolbox
    controller_interface
    geometry_msgs
    hardware_interface
    kdl_parser
    nav_msgs
    pluginlib
    realtime_tools
    roscpp
    roslint
    gazebo_ros
    tf
    urdf
)


find_package(gazebo REQUIRED)
find_package(ignition-math6 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
  LIBRARIES
    base_controller
  CATKIN_DEPENDS
    controller_interface
    hardware_interface
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
)

### LIBS
add_library(base_controller
        src/base_controller.cpp
        include/plugins/base_controller.h)
target_link_libraries(base_controller
  ${catkin_LIBRARIES}
  ${GAZEBO_LIBRARIES}
)

### TESTS
roslint_cpp()

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)

  roslaunch_add_file_check(launch)
endif()


### INSTALLS
install(TARGETS base_controller
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY config/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config)
install(DIRECTORY launch/ DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch)
