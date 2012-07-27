# DOXYGEN SUPPORT
include $(top_srcdir)/aminclude.am

SUBDIRS=ortpextension include/ortpextension example

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ortpextension.pc

EXTRA_DIST = \
	autogen.sh \
$(DX_CONFIG)

if DX_COND_doc

all: doxygen-doc

endif

MOSTLYCLEANFILES = $(DX_CLEANFILES)