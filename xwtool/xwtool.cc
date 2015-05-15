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

#include "xwtool.hh"
#include <getopt.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
  std::vector<xw::method> methods;
  xw::rpc_parse_context ctx(&methods);
  std::string err;

  try {
    picojson::_parse(ctx, std::istream_iterator<char>(std::cin),
                     std::istream_iterator<char>(), &err);
  } catch (std::runtime_error const& e) {
    std::cerr << "parse error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  for (auto method : methods) {
    method.print(std::cout);
  }

  return EXIT_SUCCESS;
}
