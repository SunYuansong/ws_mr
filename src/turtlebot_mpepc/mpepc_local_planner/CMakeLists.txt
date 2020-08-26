cmake_minimum_required(VERSION 2.8.3)
project(mpepc_local_planner)

find_package(catkin REQUIRED COMPONENTS
  angles
  base_local_planner
  cmake_modules
  costmap_2d
  dynamic_reconfigure
  nav_core
  nav_msgs
  pluginlib
  roscpp
  roslib
  tf
  )

find_package(NLopt REQUIRED)
set(NLopt_INCLUDE_DIRS ${NLOPT_INCLUDE_DIR})

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system thread)

link_directories(${catkin_LIBRARY_DIRS})

generate_dynamic_reconfigure_options(
  cfg/MPEPCPlanner.cfg
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  EgoGoal.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${NLOPT_INCLUDE_DIR}
  )

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES mpepc_local_planner
    CATKIN_DEPENDS
        dynamic_reconfigure
        pluginlib
        roscpp
)

add_library(mpepc_local_planner
  src/mpepc_planner_ros.cpp
  src/control_law.cpp
  )
  
add_dependencies(mpepc_local_planner
  ${mpepc_local_planner_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS})
target_link_libraries(mpepc_local_planner 
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
  ${NLOPT_LIBRARIES}
  )

add_dependencies(mpepc_local_planner mpepc_local_planner_gencfg)
add_dependencies(mpepc_local_planner nav_msgs_generate_messages_cpp)

install(TARGETS mpepc_local_planner
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  )

install(FILES blp_plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)



