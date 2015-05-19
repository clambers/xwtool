#ifndef XW_UTIL_HH
#define XW_UTIL_HH

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
#include "picojson.h"
#include <string>
#include <initializer_list>

namespace xw {
  template<typename> struct typestr {
    static char const* js();
  };

#define IS(x,y)                                 \
  template<> struct typestr<x> {                \
    static char const* js() { return #y; }      \
  };
  IS(picojson::array, Array)
  IS(picojson::object, Object)
  IS(double, Number)
  IS(bool, Boolean)
  IS(std::string, String)
#undef IS

  class formatter {
  public:
    formatter(std::ostream&);
    virtual ~formatter();

  protected:
    std::ostream out;
  };

  class include_guard : public formatter {
  public:
    include_guard(std::ostream&, std::string const&);
    virtual ~include_guard();
  };

  class cpp_include : public formatter {
  public:
    cpp_include(std::ostream&, std::string const&);
    cpp_include(std::ostream&, std::initializer_list<std::string>);
    virtual ~cpp_include();
  };
}

#endif
