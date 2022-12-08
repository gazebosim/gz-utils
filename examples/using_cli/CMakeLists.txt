cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ignition-utils-cli-demo)

# Find the Gazebo Libraries used directly by the example
find_package(ignition-utils1 REQUIRED COMPONENTS cli)
set(IGN_UTILS_VER ${ignition-utils1_VERSION_MAJOR})

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(
  ${PROJECT_NAME}
  ignition-utils${IGN_UTILS_VER}::cli
)
