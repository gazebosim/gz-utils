cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

#============================================================================
# Initialize the project
#============================================================================
project(ignition-utils1 VERSION 1.4.0)

#============================================================================
# Find ignition-cmake
#============================================================================
# If you get an error at this line, you need to install ignition-cmake
find_package(ignition-cmake2 2.0.0 REQUIRED)

#============================================================================
# Configure the project
#============================================================================
set(c++standard 17)
ign_configure_project(VERSION_SUFFIX)

#============================================================================
# Set project-specific options
#============================================================================

option(
  IGN_UTILS_VENDOR_CLI11
  "If true, use the vendored version of CLI11, otherwise use an external one"
  true)

#============================================================================
# Search for project-specific dependencies
#============================================================================

if(NOT IGN_UTILS_VENDOR_CLI11)
  # PKGCONFIG_IGNORE can be removed once pkg-config support in CLI11 (see
  # https://github.com/CLIUtils/CLI11/pull/523) is released
  ign_find_package(CLI11 REQUIRED_BY cli PKGCONFIG_IGNORE)
endif()

#============================================================================
# Configure the build
#============================================================================
configure_file("${PROJECT_SOURCE_DIR}/coverage.ignore.in"
               ${PROJECT_BINARY_DIR}/coverage.ignore)
ign_configure_build(QUIT_IF_BUILD_ERRORS
  COMPONENTS cli)

#============================================================================
# Create package information
#============================================================================
ign_create_packages()

#============================================================================
# Configure documentation
#============================================================================
configure_file(${CMAKE_SOURCE_DIR}/api.md.in ${CMAKE_BINARY_DIR}/api.md)
configure_file(${CMAKE_SOURCE_DIR}/tutorials.md.in ${CMAKE_BINARY_DIR}/tutorials.md)

ign_create_docs(
  API_MAINPAGE_MD "${CMAKE_BINARY_DIR}/api.md"
  TUTORIALS_MAINPAGE_MD "${CMAKE_BINARY_DIR}/tutorials.md")
