cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ignition-utils-cli-demo)

# Find the Ignition Libraries used directly by the example
find_package(ignition-utils2 REQUIRED COMPONENTS cli)
set(IGN_UTILS_VER ${ignition-utils2_VERSION_MAJOR})

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(
  ${PROJECT_NAME}
  ignition-utils${IGN_UTILS_VER}::cli
)
