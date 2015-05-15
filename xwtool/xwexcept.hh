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

#include <exception>
#include <stdexcept>
#include <sstream>

namespace xw {
  class bad_value : public std::runtime_error {
  public:
    bad_value(std::string const&);
    virtual char const* what() const throw() override;

  private:
    static std::ostringstream msg;
    std::string value;
  };
}

std::ostringstream xw::bad_value::msg;

#endif
