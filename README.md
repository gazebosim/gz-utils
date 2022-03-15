# Ignition Utils : Classes and functions for robot applications

**Maintainer:** addisu AT openrobotics DOT org

[![GitHub open issues](https://img.shields.io/github/issues-raw/ignitionrobotics/ign-utils.svg)](https://github.com/ignitionrobotics/ign-utils/issues)
[![GitHub open pull requests](https://img.shields.io/github/issues-pr-raw/ignitionrobotics/ign-utils.svg)](https://github.com/ignitionrobotics/ign-utils/pulls)
[![Discourse topics](https://img.shields.io/discourse/https/community.gazebosim.org/topics.svg)](https://community.gazebosim.org)
[![Hex.pm](https://img.shields.io/hexpm/l/plug.svg)](https://www.apache.org/licenses/LICENSE-2.0)

Build | Status
-- | --
Test coverage | [![codecov](https://codecov.io/gh/ignitionrobotics/ign-utils/branch/main/graph/badge.svg)](https://codecov.io/gh/ignitionrobotics/ign-utils)
Ubuntu Focal | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_utils-ci-main-focal-amd64)](https://build.osrfoundation.org/job/ignition_utils-ci-main-focal-amd64)
Homebrew      | [![Build Status](https://build.osrfoundation.org/buildStatus/icon?job=ignition_utils-ci-main-homebrew-amd64)](https://build.osrfoundation.org/job/ignition_utils-ci-main-homebrew-amd64)
Windows       | [![Build Status](https://build.osrfoundation.org/job/ign_utils-ci-win/badge/icon)](https://build.osrfoundation.org/job/ign_utils-ci-win/)

Ignition Utils, a component of [Ignition
Robotics](https://ignitionrobotics.org), provides general purpose
classes and functions designed for robotic applications.

# Table of Contents

[Features](#features)

[Install](#install)

[Usage](#usage)

[Documentation](#documentation)

[Testing](#testing)

[Folder Structure](#folder-structure)

[Code of Conduct](#code-of-conduct)

[Contributing](#code-of-contributing)

[Versioning](#versioning)

[License](#license)

# Features

Ignition Utils provides a wide range of functionality, including:

* A helper class to implement the PIMPL pattern
* A command line parsing utility (vendored [CLI11](https://github.com/CLIUtils/CLI11/))
* Macros to suppress warnings

# Install

See the [installation tutorial](https://ignitionrobotics.org/api/utils/0.1/install.html).

# Usage

Please refer to the [examples directory](https://github.com/ignitionrobotics/ign-utils/blob/main/examples/).

# Documentation

API and tutorials can be found at [https://ignitionrobotics.org/libs/utils](https://ignitionrobotics.org/libs/utils).

You can also generate the documentation from a clone of this repository by following these steps.

1. You will need Doxygen. On Ubuntu Doxygen can be installed using

    ```
    sudo apt-get install doxygen
    ```

2. Clone the repository

    ```
    git clone https://github.com/ignitionrobotics/ign-utils
    ```

3. Configure and build the documentation.

    ```
    cd ign-utils; mkdir build; cd build; cmake ../; make doc
    ```

4. View the documentation by running the following command from the build directory.

    ```
    firefox doxygen/html/index.html
    ```

# Testing

Follow these steps to run tests and static code analysis in your clone of this repository.

1. Follow the [source install instruction](https://ignitionrobotics.org/libs/utils#source-install).

2. Run tests.

    ```
    make test
    ```

3. Static code checker.

    ```
    make codecheck
    ```

# Folder Structure

Refer to the following table for information about important directories and files in this repository.

```
ign-utils
├── examples                 Example programs.
├── include/ignition/utils   Header files.
├── src                      Source files and unit tests.
├── test
│    ├── integration         Integration tests.
│    ├── performance         Performance tests.
│    └── regression          Regression tests.
├── tutorials                Tutorials, written in markdown.
├── Changelog.md             Changelog.
└── CMakeLists.txt           CMake build script.
```
# Contributing

Please see
[CONTRIBUTING.md](https://ignitionrobotics.org/docs/all/contributing).

# Code of Conduct

Please see
[CODE_OF_CONDUCT.md](https://github.com/ignitionrobotics/ign-utils/blob/main/CODE_OF_CONDUCT.md)

# Versioning

This library uses [Semantic Versioning](https://semver.org/).
Additionally, this library is part of the
[Ignition project](https://ignitionrobotics.org) which periodically
releases a versioned set of compatible and complimentary libraries. See the
[Ignition website](https://ignitionrobotics.org) for version and
release information.

# License

This library is licensed under
[Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0).
See also the
[LICENSE](https://github.com/ignitionrobotics/ign-utils/blob/main/LICENSE)
file.

