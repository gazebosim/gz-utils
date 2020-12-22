
add_library(implptr_test_classes SHARED implptr_test_classes.cc)

ign_build_tests(TYPE INTEGRATION SOURCES ImplPtr_TEST.cc)

target_link_libraries(INTEGRATION_ImplPtr_TEST
  implptr_test_classes
)

