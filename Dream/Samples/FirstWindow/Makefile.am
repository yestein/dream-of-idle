INCLUDES = -I$(top_srcdir)/cegui/include -I$(top_srcdir)/Samples/common/include

noinst_PROGRAMS = FirstWindow@cegui_bsfx@
noinst_HEADERS = Sample_FirstWindow.h
FirstWindow@cegui_bsfx@_SOURCES = Sample_FirstWindow.cpp
FirstWindow@cegui_bsfx@_LDADD = $(top_builddir)/cegui/src/libCEGUIBase@cegui_bsfx@.la \
                    $(top_builddir)/Samples/common/src/libCEGUISampleHelper@cegui_bsfx@.la

install-exec-local:
	$(LN_S) -f `pwd`/.libs/FirstWindow@cegui_bsfx@$(EXEEXT) $(top_builddir)/bin/FirstWindow@cegui_bsfx@$(EXEEXT)
