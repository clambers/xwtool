#include "xwapplication.hh"
#include "xwcontext.hh"
#include <config.h>
#include <getopt.h>
#include <cstdlib>
#include <iostream>

using namespace xw;

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

  while ((ch = getopt_long(*argc, *argv, ":hvo:", lopts, NULL)) != -1) {
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
      opath = optarg;
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
    while (optind < *argc) {
      std::cout << (*argv)[optind++] << std::endl;
    }
  }
}

application::~application() {}

specification application::parse() {
  std::ifstream file;
  specification methods;
  rpc_parse_context ctx(&methods);
  std::string err;

  try {
    picojson::_parse(ctx, std::istream_iterator<char>(std::cin),
                     std::istream_iterator<char>(), &err);
  } catch (std::runtime_error const& e) {
    out() << "parse error: " << e.what() << std::endl;
  }

  if (!err.empty()) {
    out() << err << std::endl;
  }

  return methods;
}

std::ostream& application::out() {
  if (!opath.empty()) {
    return std::ofstream(opath, std::ios::out);
  } else {
    return std::cout;
  }
}
