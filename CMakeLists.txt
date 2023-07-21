cmake_minimum_required(VERSION 3.12)

#============================================================================
# Initialize the project
#============================================================================
project(gz-utils)

find_package(ament_cmake_gazebo REQUIRED)
find_package(cli11_vendor REQUIRED)

set(DESIGNATION utils)

#============================================================================
# gz-utils core
#============================================================================
add_library(
  gz-utils
  src/Environment.cc
)


gz_generate_export_header(
  TARGET gz-utils
  DESIGNATION "${DESIGNATION}"
  PROJECT_INCLUDE_DIR "gz/${DESIGNATION}"
)

gz_generate_version_header(
  DESIGNATION "${DESIGNATION}"
  PROJECT_INCLUDE_DIR "gz/${DESIGNATION}"
)

gz_generate_project_header(
  DESIGNATION "${DESIGNATION}"
  PROJECT_INCLUDE_DIR "gz/${DESIGNATION}"
  SOURCE_INCLUDE_DIR include
)

target_include_directories(gz-utils PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")

install(TARGETS gz-utils EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(
  DIRECTORY include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hh"
)

#============================================================================
# gz-utils-cli
#============================================================================

add_library(
  gz-utils-cli
  INTERFACE
)

target_include_directories(gz-utils-cli INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cli/include/>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cli/include/external-cli>"
  "$<INSTALL_INTERFACE:include>")


target_link_libraries(gz-utils-cli INTERFACE gz-utils)

install(TARGETS gz-utils-cli EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

install(
  DIRECTORY cli/include/gz
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)

install(
  DIRECTORY cli/include/external-cli/gz
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)


#============================================================================
# Tests
#============================================================================

if (BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(UNIT_Environment_TEST src/Environment_TEST.cc)
  if (TARGET UNIT_Environment_TEST)
    target_link_libraries(UNIT_Environment_TEST gz-utils)
  endif()

  ament_add_gtest(UNIT_NeverDestroyed_TEST src/NeverDestroyed_TEST.cc)
  if (TARGET UNIT_NeverDestroyed_TEST)
    target_link_libraries(UNIT_NeverDestroyed_TEST gz-utils)
  endif()

  ament_add_gtest(UNIT_cli_TEST cli/src/cli_TEST.cc)
  if (TARGET UNIT_cli_TEST)
    target_link_libraries(UNIT_cli_TEST gz-utils-cli)
  endif()

  add_executable(subprocess_main test/integration/subprocess/subprocess_main.cc)
  if (TARGET subprocess_main)
    target_link_libraries(subprocess_main gz-utils-cli)
  endif()

  ament_add_gtest(INTEGRATION_subprocess_TEST test/integration/subprocess_TEST.cc)
  if (TARGET INTEGRATION_subprocess_TEST)
    target_link_libraries(INTEGRATION_subprocess_TEST gz-utils)
    target_compile_definitions(INTEGRATION_subprocess_TEST PRIVATE "-DSUBPROCESS_EXECUTABLE_PATH=\"$<TARGET_FILE:subprocess_main>\"")
  endif()
endif()

ament_export_targets(${PROJECT_NAME})

ament_package()
