/**
 * Copyright (C) 2015 Chris Lamberson <clamberson@gmail.com>.
 *
 * This file is part of XWtool.
 *
 * XWtool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * XWtool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with XWtool. If not, see <http://www.gnu.org/licenses/>.
 */

#include "xwspec.hh"
#include "xwutil.hh"

using namespace xw;

method::method() {}

method::method(type& json) {
  name = json["name"].get<name_type>();
  params = json["params"].get<params_type>();
}

method::~method() {}

void method::dump(std::ostream& out) {
  out << "exports." << name << " = function(";
  std::copy(std::begin(params), std::end(params),
            signature_maker<params_type::value_type>(out, ", "));
  out
    << ") {" << std::endl
    << "  var id = callbacks.setup(callback);" << std::endl
    << "  var msg = {" << std::endl
    << "    method: \"" << name << "\"," << std::endl
    << "    params: {" << std::endl
    << "      ";
  std::copy(std::begin(params), std::end(params),
            params_builder<params_type::value_type>(out, "      "));
  out
    << "    }" << std::endl
    << "  };" << std::endl
    << "  postMessage(id, msg);" << std::endl
    << "};" << std::endl
    << std::endl;
}
