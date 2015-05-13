AX_V_TEST = $(AX_V_TEST_$(V))
AX_V_TEST_ = $(AX_V_TEST_$(AM_DEFAULT_VERBOSITY))
AX_V_TEST_0 = @echo "  TEST    " `basename $<`;
AX_V_TEST_1 =
