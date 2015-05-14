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

#include "xwtoolize.hh"
#include <config.h>
#include <getopt.h>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  int ch;

  while (1) {
    static struct option long_options[] = {
      { "help",    no_argument, 0, 'h' },
      { "version", no_argument, 0, 'v' },
      { 0, 0, 0, 0 }
    };

    int optind = 0;

    ch = getopt_long(argc, argv, "hv", long_options, &optind);

    if (ch == -1) {
      break;
    }

    switch (ch) {
    case 'h':
      do_help();
      goto done;

    case 'v':
      do_version();
      goto done;
    }
  }

  install_scripts();

 done:
  return EXIT_SUCCESS;
}

void do_help() {
  std::cout << "Help string" << std::endl;
}

void do_version() {
  std::cout << PACKAGE_STRING << std::endl;
}

void install_scripts() {
  std::cout << "xwtoolize: installing scripts" << std::endl;
}
