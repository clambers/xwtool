#ifndef XW_CONTEXT_HH
#define XW_CONTEXT_HH

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
#include "xwexcept.hh"
#include "picojson.h"

namespace xw {
  class rpc_parse_context : public picojson::deny_parse_context {
  public:
    template<typename T> using input = picojson::input<T>;

    rpc_parse_context(specification* m);
    bool parse_array_start();
    bool parse_array_stop(size_t);
    template<typename T> bool parse_array_item(input<T>& in, size_t);

  private:
    specification spec;
    specification* out;
  };

  template<typename T>
  bool rpc_parse_context::parse_array_item(input<T>& in, size_t) {
    picojson::value value;
    picojson::default_parse_context ctx(&value);
    method::type meth;

    if (!picojson::_parse(ctx, in)) {
      return false;
    }

    if (!value.is<method::type>()) {
      throw bad_type<method::type>(value);
    }

    if (!value.contains("name")) {
      throw object_error(value, "has no name");
    }

    if (!value.contains("params")) {
      throw method_error(value, "has no params");
    }

    return true;
  }
}

#endif
