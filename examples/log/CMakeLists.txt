cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
project(gz-utils-logger-demo)

# Find the Gazebo Libraries used directly by the example
find_package(gz-utils REQUIRED COMPONENTS log)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(
  ${PROJECT_NAME}
  gz-utils::log
)
