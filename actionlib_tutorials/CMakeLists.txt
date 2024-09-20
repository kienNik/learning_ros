cmake_minimum_required(VERSION 3.0.2)
project(actionlib_tutorials)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  roscpp
  rospy
  std_msgs
)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
add_action_files(
  FILES
  Fibonacci.action
  Averaging.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  actionlib_msgs
  std_msgs
)

catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES actionlib_tutorials
 CATKIN_DEPENDS actionlib actionlib_msgs message_generation roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


add_executable(fibonacci_server src/fibonacci_server.cpp)
add_dependencies(fibonacci_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(fibonacci_server ${catkin_LIBRARIES})

add_executable(fibonacci_client src/fibonacci_client.cpp)
add_dependencies(fibonacci_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(fibonacci_client ${catkin_LIBRARIES})

add_executable(averaging_server src/averaging_server.cpp)
add_dependencies(averaging_server ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(averaging_server ${catkin_LIBRARIES})

add_executable(averaging_client src/averaging_client.cpp)
add_dependencies(averaging_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(averaging_client ${catkin_LIBRARIES})
