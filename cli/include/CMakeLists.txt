# As the include headers in the source tree are not in the usual location
# to support the vendored and not vendored case, we need to manually call
# add_subdirectory of the correct directory, and
# target_include_directories(@tgt@ INTERFACE "$<BUILD_INTERFACE:@incl_dirs>")
# that for the usual include directories are handled by ign_add_component
if(IGN_UTILS_VENDOR_CLI11)
  add_subdirectory(vendored-cli/ignition/utils)
  target_include_directories(${ign_utils_cli_target_name} 
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cli/include/vendored-cli>")
else()
  add_subdirectory(external-cli/ignition/utils)
  target_include_directories(${ign_utils_cli_target_name} 
    INTERFACE 
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cli/include/external-cli>")
endif()
