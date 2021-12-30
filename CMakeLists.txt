cmake_minimum_required(VERSION 3.5)
project(ros_template)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(
  include
)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_index_cpp REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rosidl_default_generators REQUIRED)

ament_export_dependencies(rosidl_default_runtime)

rosidl_generate_interfaces(${PROJECT_NAME}
  msg/Info.msg
  srv/Trigger.srv
)

add_executable(pub
  src/pub.cpp
  src/main.cpp
)
ament_target_dependencies(pub rclcpp std_msgs)
rosidl_target_interfaces(pub
  # In order to use the messages generated in the same
  # package we need to use the following CMake code
  ${PROJECT_NAME} rosidl_typesupport_cpp)

add_executable(srv_server src/srv_server.cpp)
ament_target_dependencies(srv_server rclcpp)
rosidl_target_interfaces(srv_server ${PROJECT_NAME} rosidl_typesupport_cpp)

add_executable(srv_client src/srv_client.cpp)
ament_target_dependencies(srv_client rclcpp)
rosidl_target_interfaces(srv_client ${PROJECT_NAME} rosidl_typesupport_cpp)

install(TARGETS
  pub
  srv_server
  srv_client
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
