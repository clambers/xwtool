# Copyright (C) 2015 Chris Lamberson <clamberson@gmail.com>.
#
# This file is part of XWtool.
#
# XWtool is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# XWtool is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with XWtool. If not, see <http://www.gnu.org/licenses/>.

AC_PREREQ([2.69])

AC_INIT([XWtool], [1.0], [https://github.com/dutch/xwtool/issues], [],
[https://github.com/dutch/xwtool])
AC_COPYRIGHT([Copyright (C) 2015 Chris Lamberson <clamberson@gmail.com>.])
AC_CONFIG_SRCDIR([xwtool/xwtool.cc])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_TESTDIR([tests])

AM_INIT_AUTOMAKE([1.14 foreign -Wall -Werror -Wno-portability])
AM_SILENT_RULES([yes])

AC_PROG_CXX

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile m4/Makefile xwtool/Makefile tests/Makefile
tests/package.m4 tests/atlocal])

AC_OUTPUT
