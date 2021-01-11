add_library(implptr_test_classes SHARED implptr_test_classes.cc)

set_target_properties(implptr_test_classes PROPERTIES
  CXX_STANDARD ${c++standard}
  CXX_STANDARD_REQUIRED ON 
)

# Piggyback on the auto-generated dll exports for Windows
target_compile_definitions(
  implptr_test_classes
  PRIVATE
  -Dignition_utils${PROJECT_VERSION_MAJOR}_EXPORTS
)

ign_build_tests(TYPE INTEGRATION SOURCES ImplPtr_TEST.cc)

target_link_libraries(INTEGRATION_ImplPtr_TEST
  implptr_test_classes
)
