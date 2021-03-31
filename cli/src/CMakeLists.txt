ign_add_component(
  cli 
  INTERFACE 
  INDEPENDENT_FROM_PROJECT_LIB
  GET_TARGET_NAME ign_utils_cli_target_name)

# Make sure that the name is visible also in cli/include/CMakeLists.txt
set(ign_utils_cli_target_name ${ign_utils_cli_target_name} PARENT_SCOPE)
if(NOT IGN_UTILS_VENDOR_CLI11)
  target_link_libraries(${ign_utils_cli_target_name} INTERFACE CLI11::CLI11)
endif() 
