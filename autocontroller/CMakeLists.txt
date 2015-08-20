cmake_minimum_required(VERSION 2.8.3)
project(autocontroller)

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  std_msgs
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
  roscpp
  rospy
  std_msgs
  message_runtime
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

add_executable(autoconpub src/autoconpub.cpp)
add_dependencies(autoconpub autocontroller_generate_messages_cpp)
target_link_libraries(autoconpub ${catkin_LIBRARIES})

add_executable(autoconsub src/autoconsub.cpp)
add_dependencies(autoconsub autocontroller_generate_messages_cpp)
target_link_libraries(autoconsub ${catkin_LIBRARIES})
