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
#include "xwcontext.hh"

#define Q(x) #x
#define QUOTE(x) Q(x)

using namespace xw;

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
