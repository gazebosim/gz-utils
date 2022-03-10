/*
 * Copyright (C) 2021 Open Source Robotics Foundation
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

#ifndef IGNITION_UTILS_CLI_IGNITION_FORMATTER_HPP_
#define IGNITION_UTILS_CLI_IGNITION_FORMATTER_HPP_

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#include "ignition/utils/cli/App.hpp"
#include "ignition/utils/cli/FormatterFwd.hpp"

namespace CLI 
{
//////////////////////////////////////////////////
/// \brief CLI Formatter class that implements custom Ignition-specific
/// formatting.
///
/// More information on custom formatters:
/// https://cliutils.github.io/CLI11/book/chapters/formatting.html
class IgnitionFormatter: public Formatter {

//////////////////////////////////////////////////
public: std::string make_option_name(
            const CLI::Option *opt, bool is_positional) const override {
  if(is_positional)
      return opt->get_name(true, false);

  return opt->get_name(false, true);
}


//////////////////////////////////////////////////
public: std::string make_option_opts(const CLI::Option *opt) const override {
    std::stringstream out;

    if(opt->get_type_size() != 0) {
        if(!opt->get_type_name().empty())
            out << " " << get_label(opt->get_type_name());
        if(!opt->get_default_str().empty())
            out << "=" << opt->get_default_str();
        if(opt->get_expected_max() == detail::expected_max_vector_size)
            out << " ...";
        else if(opt->get_expected_min() > 1)
            out << " x " << opt->get_expected();

        if(opt->get_required())
            out << " " << get_label("REQUIRED");
    }
    if(!opt->get_envname().empty())
        out << " (" << get_label("Env") << ":" << opt->get_envname() << ")";
    if(!opt->get_needs().empty()) {
        out << " " << get_label("Needs") << ":";
        for(const Option *op : opt->get_needs())
            out << " " << op->get_name();
    }
    if(!opt->get_excludes().empty()) {
        out << " " << get_label("Excludes") << ":";
        for(const Option *op : opt->get_excludes())
            out << " " << op->get_name();
    }
    return out.str();

}


//////////////////////////////////////////////////
std::string make_option_desc(const CLI::Option *opt) const override {
 return opt->get_description(); 
}
};
}  // namespace CLI

#endif  // IGNITION_UTILS_CLI_IGNITION_FORMATTER_HPP_
