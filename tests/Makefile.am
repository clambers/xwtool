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

AUTOM4TE = $(top_srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
TESTSUITE = $(top_srcdir)/tests/testsuite
TESTSUITE_AT = testsuite.at xwtool.at
EXTRA_DIST = $(TESTSUITE_AT) $(TESTSUITE)
DISTCLEANFILES = atconfig atlocal
MAINTAINERCLEANFILES = $(TESTSUITE)

AX_V_TEST = $(AX_V_TEST_$(V))
AX_V_TEST_ = $(AX_V_TEST_$(AM_DEFAULT_VERBOSITY))
AX_V_TEST_0 = @echo "  TEST    " `basename $<`;
AX_V_TEST_1 =

$(TESTSUITE): $(TESTSUITE_AT)
	$(AM_V_GEN) $(AUTOTEST) -o $@.tmp $@.at; \
	mv $@.tmp $@

check-local: $(TESTSUITE) atconfig atlocal
	$(AX_V_TEST) $(SHELL) $(TESTSUITE)

installcheck-local: $(TESTSUITE) atconfig atlocal
	$(AX_V_TEST) $(SHELL) $(TESTSUITE) AUTOTEST_PATH='$(bindir)'

clean-local:
	test ! -f $(TESTSUITE) || $(SHELL) $(TESTSUITE) --clean
