#ifndef XWTOOL_HH
#define XWTOOL_HH

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

#include "picojson.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <exception>
#include <stdexcept>

#define Q(x) #x
#define QUOTE(x) Q(x)

#define ASSERT(x)                                         \
  if (!(x)) throw std::runtime_error("assertion failed")

namespace xw {
  std::string dectype(picojson::value& v) {
#define CTYPE(t) if (v.is<t>()) return QUOTE(t)
    CTYPE(picojson::object);
    CTYPE(picojson::array);
    CTYPE(bool);
    CTYPE(double);
    CTYPE(std::string);
#undef CTYPE
    return "<undefined>";
  }

  std::string argtype(picojson::value& v) {
#define IS(t,u) if (v.is<t>()) return QUOTE(u)
    IS(picojson::object, picojson::object const&);
    IS(picojson::array, picojson::array const&);
    IS(bool, bool);
    IS(double, double);
    IS(std::string, std::string const&);
#undef IS
    return "<undefined>";
  }

  std::string jstype(picojson::value& v) {
#define IS(t,u) if (v.is<t>()) return QUOTE(u)
    IS(picojson::object, Object);
    IS(picojson::array, Array);
    IS(bool, Boolean);
    IS(double, Number);
    IS(std::string, String);
#undef IS
    return "<undefined>";
  }

  namespace exc {
    class bad_value : public std::runtime_error {
    public:
      bad_value(std::string const& value)
        : runtime_error("bad configuration value"), value(value) {}

      virtual char const* what() const throw() override {
        msg.str("");
        msg << std::runtime_error::what() << ": " << value;
        return msg.str().c_str();
      }

    private:
      static std::ostringstream msg;
      std::string value;
    };
  }

  class method {
  public:
    using type = picojson::object;
    using name_type = std::string;
    using params_type = picojson::object;
    using returns_type = picojson::value;

    method() {}

    method(type& json) : name(json["name"]),
                         params(json["params"]),
                         returns(json["returns"]) {
      if (!name.is<name_type>()) {
        throw std::runtime_error("method name not a String");
      }

      if (!params.is<params_type>()) {
        throw std::runtime_error("method params not an Object");
      }
    }

    virtual ~method() {}

    void print(std::ostream& o) {
      o << "foobar" << std::endl;
    }

  private:
    picojson::value name;
    picojson::value params;
    picojson::value returns;
  };

  namespace {
    namespace p = std::placeholders;
  }

  using specification = std::vector<method>;

  class rpc_parse_context : public picojson::deny_parse_context {
  public:
    rpc_parse_context(specification* m) : out(m) {}

    bool parse_array_start() {
      return true;
    }

    bool parse_array_stop(size_t) {
      return true;
    }

    template<typename T>
    bool parse_array_item(picojson::input<T>& in, size_t) {
      picojson::value value;
      picojson::default_parse_context ctx(&value);

      if (!picojson::_parse(ctx, in)) {
        return false;
      }

      if (value.is<picojson::object>()) {
        spec.push_back(value.get<picojson::object>());
      }

      *out = spec;

      return true;
    }

  private:
    specification spec;
    specification* out;
  };
}

#endif
