cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(gz-utils-cli-demo)

# Find the Gazebo Libraries used directly by the example
find_package(gz-utils2 REQUIRED COMPONENTS cli)
set(GZ_UTILS_VER ${gz-utils2_VERSION_MAJOR})

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(
  ${PROJECT_NAME}
  gz-utils${GZ_UTILS_VER}::cli
)
