/*
 * Copyright (C) 2018 Open Source Robotics Foundation
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

#include <gz/utils/SuppressWarning.hh>
#include <ignition/utils/config.hh>

#ifndef IGN_UTILS_WARN_IGNORE__NON_VIRTUAL_DESTRUCTOR
  #define IGN_UTILS_WARN_IGNORE__NON_VIRTUAL_DESTRUCTOR \
    DETAIL_GZ_UTILS_WARN_IGNORE__NON_VIRTUAL_DESTRUCTOR
#endif

#ifndef IGN_UTILS_WARN_RESUME__NON_VIRTUAL_DESTRUCTOR
  #define IGN_UTILS_WARN_RESUME__NON_VIRTUAL_DESTRUCTOR \
    DETAIL_GZ_UTILS_WARN_RESUME__NON_VIRTUAL_DESTRUCTOR
#endif

#ifndef IGN_UTILS_WARN_IGNORE__DLL_INTERFACE_MISSING
  #define IGN_UTILS_WARN_IGNORE__DLL_INTERFACE_MISSING \
    DETAIL_GZ_UTILS_WARN_IGNORE__DLL_INTERFACE_MISSING
#endif

#ifndef IGN_UTILS_WARN_RESUME__DLL_INTERFACE_MISSING
  #define IGN_UTILS_WARN_RESUME__DLL_INTERFACE_MISSING \
    DETAIL_GZ_UTILS_WARN_RESUME__DLL_INTERFACE_MISSING
#endif

#ifndef IGN_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION
  #define IGN_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION \
    DETAIL_GZ_UTILS_WARN_IGNORE__DEPRECATED_DECLARATION
#endif

#ifndef IGN_UTILS_WARN_RESUME__DEPRECATED_DECLARATION
  #define IGN_UTILS_WARN_RESUME__DEPRECATED_DECLARATION \
    DETAIL_GZ_UTILS_WARN_RESUME__DEPRECATED_DECLARATION
#endif
