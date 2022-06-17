# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.

## Gazebo Utils 1.X to 2.X

* The `ignition` namespace is deprecated and will be removed in future versions.
  Use `gz` instead.

* Header files under `ignition/...` are deprecated and will be removed in future versions.
  Use `gz/...` instead.

* The following `IGN_` prefixed macros are deprecated and will be removed in future versions.
  Additionally, they will only be available when including the corresponding `ignition/...` header.
  Use the `GZ_` prefix instead.
  * `IGN_UTILS_TEST_DISABLED_ON_WIN32`
  * `IGN_UTILS_TEST_DISABLED_ON_MAC`
  * `IGN_UTILS_TEST_DISABLED_ONLY_ON_LINUX`
  * `IGN_UTILS_IMPL_PTR_FWD`
  * `IGN_UTILS_UNIQUE_IMPL_PTR_FWD`
  * `IGN_UTILS_IMPL_PTR`
  * `IGN_UTILS_UNIQUE_IMPL_PTR`
  *  `IGN_UTILS_WARN_IGNORE__NON_VIRTUAL_DESTRUCTOR`, `IGN_UTILS_WARN_RESUME__NON_VIRTUAL_DESTRUCTOR`
  * `IGN_UTILS_WARN_IGNORE__DLL_INTERFACE_MISSING`, `IGN_UTILS_WARN_RESUME__DLL_INTERFACE_MISSING`
  * `IGN_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION`, `IGN_UTILS_WARN_RESUME__DEPRECATED_DECLARATION`


## Gazebo Utils 1.2 to 1.3

Recommended migration:
Utils 1.3.0 introduces the `ExtraTestMacros.hh` headers that are also in ign-cmake.
This is an effort to remove all headers from ign-cmake and locate them in ign-utils.
To update, replace all instances of `ignition/utilities/ExtraTestMacros.hh` with `ignition/utils/ExtraTestMacros.hh`
In the future, `ignition/utilities/ExtraTestMacros.hh` will be removed from ign-cmake.

## Gazebo Utils 0.X to 1.X
