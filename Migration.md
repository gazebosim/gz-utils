# Note on deprecations
A tick-tock release cycle allows easy migration to new software versions.
Obsolete code is marked as deprecated for one major release.
Deprecated code produces compile-time warnings. These warning serve as
notification to users that their code should be upgraded. The next major
release will remove the deprecated code.

## Ignition Utils 1.2 to 1.3

Recommended migration:
Utils 1.3.0 introduces the `ExtraTestMacros.hh` headers that are also in ign-cmake.
This is an effort to remove all headers from ign-cmake and locate them in ign-utils.
To update, replace all instances of `ignition/utilities/ExtraTestMacros.hh` with `ignition/utils/ExtraTestMacros.hh`
In the future, `ignition/utilities/ExtraTestMacros.hh` will be removed from ign-cmake.

## Ignition Utils 0.X to 1.X
