INCLUDES = -I$(top_srcdir)/cegui/include -I$(top_srcdir)/Samples/common/include

noinst_PROGRAMS = Demo6@cegui_bsfx@

noinst_HEADERS =  Sample_Demo6.h

Demo6@cegui_bsfx@_SOURCES = Sample_Demo6.cpp
Demo6@cegui_bsfx@_LDADD = $(top_builddir)/cegui/src/libCEGUIBase@cegui_bsfx@.la \
              $(top_builddir)/Samples/common/src/libCEGUISampleHelper@cegui_bsfx@.la


install-exec-local:
	$(LN_S) -f `pwd`/.libs/Demo6@cegui_bsfx@$(EXEEXT) $(top_builddir)/bin/Demo6@cegui_bsfx@$(EXEEXT)
