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

using namespace xw;

method::method() {}

method::method(type& json) : name(json["name"]), params(json["params"]),
                             returns(json["returns"]) {
  if (!name.is<name_type>()) {
    throw std::runtime_error("method name not a String");
  }

  if (!params.is<params_type>()) {
    throw std::runtime_error("method params not an Object");
  }
}

method::~method() {}

void method::dump(std::ostream& o) {
  o << "foobar" << std::endl;
}
