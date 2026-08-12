/*
 * Copyright (C) 2026 Open Source Robotics Foundation
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

#include <gtest/gtest.h>
#include <string>

#include <gz/utils/SuppressWarning.hh>

class BaseWithoutVirtualDestructor
{
  public: virtual void DoSomething() {}
};

class DerivedWithoutVirtualDestructor : public BaseWithoutVirtualDestructor
{
};

// GZ_UTILS_WARN_IGNORE__DLL_INTERFACE_MISSING
class
#ifdef _MSC_VER
  __declspec(dllexport)
#endif
DllInterfaceClass
{
  private: std::string someString;
};
// GZ_UTILS_WARN_RESUME__DLL_INTERFACE_MISSING

// GZ_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION
[[deprecated]]
void DeprecatedFunction()
{
}
// GZ_UTILS_WARN_RESUME__DEPRECATED_DECLARATION

/////////////////////////////////////////////////
TEST(SuppressWarning, NonVirtualDestructor)
{
  BaseWithoutVirtualDestructor *ptr = new DerivedWithoutVirtualDestructor();
  // GZ_UTILS_WARN_IGNORE__NON_VIRTUAL_DESTRUCTOR
  delete ptr;
  // GZ_UTILS_WARN_RESUME__NON_VIRTUAL_DESTRUCTOR
}

/////////////////////////////////////////////////
TEST(SuppressWarning, DeprecatedDeclaration)
{
  // GZ_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION
  DeprecatedFunction();
  // GZ_UTILS_WARN_RESUME__DEPRECATED_DECLARATION
}

/////////////////////////////////////////////////
TEST(SuppressWarning, SwitchNoDefault)
{
  enum class MyEnum { A, B };
  MyEnum e = MyEnum::A;

  // GZ_UTILS_WARN_IGNORE__SWITCH_NO_DEFAULT_STATEMENT
  switch (e)
  {
    case MyEnum::A:
      break;
    case MyEnum::B:
      break;
  }
  // GZ_UTILS_WARN_RESUME__SWITCH_NO_DEFAULT_STATEMENT
}
