cmake_minimum_required(VERSION 2.8.3)
project(ropod_tue_2_bringup)

find_package(catkin REQUIRED COMPONENTS
    message_generation
    geometry_msgs
    tf2_geometry_msgs
    nav_msgs
    roscpp
    tf
)


# find_package(Boost REQUIRED COMPONENTS system program_options)
# find_package(PCL REQUIRED)
# find_package(OpenCV REQUIRED)

# ------------------------------------------------------------------------------------------------
#                                     ROS MESSAGES AND SERVICES
# ------------------------------------------------------------------------------------------------

# Generate messages
# add_message_files(
#    FILES
#    message1.msg
#    ...
# )

# Generate services
# add_service_files(
#    FILES
#    service1.srv
#    ...
# )

# Generate added messages and services with any dependencies listed here
# generate_messages(
#    DEPENDENCIES
#    geometry_msgs
#    ...
# )

# ------------------------------------------------------------------------------------------------
#                                          CATKIN EXPORT
# ------------------------------------------------------------------------------------------------

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ropod_bringup
#  CATKIN_DEPENDS geometry_msgs roscpp tf
#  DEPENDS system_lib
)

# ------------------------------------------------------------------------------------------------
#                                              BUILD
# ------------------------------------------------------------------------------------------------

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

# add_library(library_name
#     src/lib_source_file1.cpp
#     ...
# )
# target_link_libraries(library_name ${catkin_LIBRARIES})

# add_executable(exec_name
#     src/source_file1.cpp
#     ...
# )
# target_link_libraries(exec_name ${catkin_LIBRARIES})

add_executable(ropod_tf_broadcaster_simulator src/ropod_tf_broadcaster_simulator.cpp)
target_link_libraries(ropod_tf_broadcaster_simulator ${catkin_LIBRARIES})

add_executable(ropod_mobidik_tf_broadcaster_simulator src/ropod_mobidik_tf_broadcaster_simulator.cpp)
target_link_libraries(ropod_mobidik_tf_broadcaster_simulator ${catkin_LIBRARIES})

add_executable(ropod_mobidik_tf_broadcaster src/ropod_mobidik_tf_broadcaster.cpp)
target_link_libraries(ropod_mobidik_tf_broadcaster ${catkin_LIBRARIES})

add_executable(ropod_mobidik_tf_broadcaster_only_ropod src/ropod_mobidik_tf_broadcaster_only_ropod.cpp)
target_link_libraries(ropod_mobidik_tf_broadcaster_only_ropod ${catkin_LIBRARIES})

add_executable(laserBack_NoiseReduction src/laserBack_NoiseReduction.cpp)
target_link_libraries(laserBack_NoiseReduction ${catkin_LIBRARIES})
