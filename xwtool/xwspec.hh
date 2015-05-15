#ifndef XW_SPEC_HH
#define XW_SPEC_HH

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
#include <string>
#include <vector>

namespace xw {
  class method {
  public:
    using type = picojson::object;
    using name_type = std::string;
    using params_type = picojson::object;
    using returns_type = picojson::value;

    method();
    method(type&);
    virtual ~method();
    void dump(std::ostream&);

  private:
    picojson::value name;
    picojson::value params;
    picojson::value returns;
  };

  using specification = std::vector<method>;
}

#endif
