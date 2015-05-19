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
#include "xwexcept.hh"
#include "xwcontext.hh"
#include <config.h>
#include <getopt.h>
#include <cstdlib>
#include <iostream>

using namespace xw;

application::application() {}

application::application(int* argc, char*** argv) : argc(*argc), argv(*argv) {}

application::~application() {}

void application::run() {
  int do_help = 0;
  int do_version = 0;
  int do_output = 0;
  char ch;
  std::string outpath;

  static struct option lopts[] = {
    {"help", no_argument, &do_help, 1},
    {"version", no_argument, &do_version, 1},
    {"output", required_argument, nullptr, 'o'},
    {0,0,0,0}
  };

  while ((ch = getopt_long(argc, argv, ":hvo:", lopts, nullptr)) != -1) {
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
      std::cerr << argv[0]
                << ": option -"
                << optopt
                << " requires an argument"
                << std::endl;
      break;

    case '?':
      std::cerr << argv[0]
                << ": option -"
                << optopt
                << " not recognized: ignored"
                << std::endl;
      break;
    }
  }

  if (do_help) {
    std::cout
      << "Usage: xwtool [options] [file]" << std::endl
      << std::endl
      << "Process a JSON file and generate a C++ XW header." << std::endl
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

  if (!(optind < argc)) {
    throw xwtool_error("no input files");
  }

  std::ifstream infile(argv[optind]);
  if (!infile.is_open()) {
    throw xwtool_error(std::string("error opening '") + argv[optind] + "'");
  }

  specification methods;
  rpc_parse_context ctx(&methods);
  std::string err;

  picojson::_parse(ctx, std::istream_iterator<char>(infile),
                   std::istream_iterator<char>(), &err);

  if (!err.empty()) {
    throw xwtool_error(err);
  }

  std::ofstream outfile(!outpath.empty() ? outpath : "api.out");

  for (auto method : methods) {
    method.dump(outfile);
  }
}
