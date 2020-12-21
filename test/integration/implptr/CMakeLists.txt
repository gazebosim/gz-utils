
add_library(pimpl SHARED classes.cc)

ign_build_tests(TYPE INTEGRATION SOURCES ImplPtr_TEST.cc)

target_link_libraries(INTEGRATION_ImplPtr_TEST
  pimpl
)

