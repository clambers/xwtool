#ifndef XW_EXCEPT_HH
#define XW_EXCEPT_HH

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

#include "xwutil.hh"
#include "xwspec.hh"
#include "picojson.h"
#include <exception>
#include <stdexcept>
#include <sstream>

namespace xw {
  class xwtool_error : public std::runtime_error {
  public:
    xwtool_error(std::string const&);
    virtual char const* what() const throw() override;

  private:
    static std::ostringstream msg;
    std::string err;
  };

  class object_error : public xwtool_error {
  public:
    object_error(picojson::value&, std::string const&);
    virtual char const* what() const throw() override;

  private:
    static std::ostringstream msg;
    std::string issue;
  };

  class method_error : public object_error {
  public:
    method_error(picojson::value&, std::string const&);
  };

  template<typename T>
  class bad_type : public xwtool_error {
  public:
    bad_type(picojson::value const&);
    virtual char const* what() const throw() override;

  private:
    static std::ostringstream msg;
    std::string value;
  };

  template<typename T> std::ostringstream bad_type<T>::msg;

  template<typename T> bad_type<T>::bad_type(picojson::value const& value)
    : xwtool_error("wrong type for "
                   + value.serialize()
                   + " (expected "
                   + typestr<T>::js()
                   + ")") {}

  template<typename T> char const* bad_type<T>::what() const throw() {
    msg.str("");
    msg << xwtool_error::what();
    return msg.str().c_str();
  }
}

#endif
