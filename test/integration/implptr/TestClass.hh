/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef IMPLPTR__TESTCLASS_HH_
#define IMPLPTR__TESTCLASS_HH_

#include <ignition/utils/ImplPtr.hh>
#include <ignition/utils/Export.hh>

// Forward declaration of implementation class
class TestClassImpl;


/// \class TestClass TestClass.hh
/// \brief A simple test class utilizing an impl_ptr
class IGNITION_UTILS_VISIBLE TestClass {

  public: TestClass(const std::string &_testText);

  public: std::string GetTestText() const;

  public: ignition::utils::impl_ptr<TestClassImpl> dataPtr;
};

/// \class TestClassUnique TestClass.hh
/// \brief A simple test class utilizing a unique impl_ptr
class IGNITION_UTILS_VISIBLE TestClassUnique {

  public: TestClassUnique(const std::string &_testText);

  public: std::string GetTestText() const;

  public: ignition::utils::unique_impl_ptr<TestClassImpl> dataPtr;
};

#endif  // IMPLPTR__TESTCLASS_HH_
