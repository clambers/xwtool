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

#include "xwapplication.hh"
#include "xwcontext.hh"
#include <config.h>
#include <getopt.h>
#include <cstdlib>
#include <iostream>

using namespace xw;

cout_redirector::cout_redirector(std::string path) {
  if (!path.empty()) {
    of.open(path, std::ios_base::out);
    old = std::cout.rdbuf(&of);
  }
}

cout_redirector::~cout_redirector() {
  std::cout.rdbuf(old);
}

application::application() {}

application::application(int* argc, char*** argv) {
  int do_help = 0;
  int do_version = 0;
  int do_output = 0;
  char ch;

  static struct option lopts[] = {
    {"help", no_argument, &do_help, 1},
    {"version", no_argument, &do_version, 1},
    {"output", required_argument, nullptr, 'o'},
    {0,0,0,0}
  };

  while ((ch = getopt_long(*argc, *argv, ":hvo:", lopts, nullptr)) != -1) {
    switch (ch) {
    case 0:
      break;

    case 'h':
      do_help = 1;
      break;

    case 'v':
      do_version = 1;
      break;

    case 'o':
      outpath = optarg;
      break;

    case ':':
      std::cerr << *argv[0]
                << ": option -"
                << optopt
                << " requires an argument"
                << std::endl;
      break;

    case '?':
      std::cerr << *argv[0]
                << ": option -"
                << optopt
                << " not recognized: ignored"
                << std::endl;
      break;
    }
  }

  if (do_help) {
    std::cout << "Usage: xwtool [options] [file]" << std::endl
              << std::endl
              << "Options:" << std::endl
              << "  -h, --help     print this message" << std::endl
              << "  -v, --version  print version information" << std::endl
              << "  -o, --output   output file" << std::endl;
    exit(EXIT_SUCCESS);
  }

  if (do_version) {
    std::cout << PACKAGE_STRING << std::endl;
    exit(EXIT_SUCCESS);
  }

  if (optind < *argc) {
    outpath = (*argv)[optind];
  }
}

application::~application() {}

int application::run() {
  cout_redirector cm(outpath);
  specification methods;
  rpc_parse_context ctx(&methods);
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
    std::cout << "method: ";
    method.dump(std::cout);
    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
