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

#include "xwexcept.hh"

using namespace xw;

std::ostringstream xwtool_error::msg;
std::ostringstream object_error::msg;

xwtool_error::xwtool_error(std::string const& err)
  : std::runtime_error("xwtool: "), err(err) {}

char const* xwtool_error::what() const throw() {
  msg.str("");
  msg << std::runtime_error::what() << err;
  return msg.str().c_str();
}

object_error::object_error(picojson::value& value,
                           std::string const& issue)
  : xwtool_error("method '" + value.serialize() + "' "), issue(issue) {}

char const* object_error::what() const throw() {
  msg.str("");
  msg << xwtool_error::what() << issue;
  return msg.str().c_str();
}

method_error::method_error(picojson::value& value,
                           std::string const& issue)
  : object_error(value.get<method::type>()["name"], issue) {}
