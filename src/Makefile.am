#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libortpextension.la

#######################################
# Build information for each library

# Sources for libortpextension
libortpextension_la_SOURCES = \
	extension_utils.c \
	rtp_extension.c \
	rtpsession_extension.c


# Linker options libTestProgram
libortpextension_la_LDFLAGS = \
		@ortp_LIBS@

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libortpextension_la_CFLAGS = \
		-I$(top_srcdir)/include \
		@ortp_CFLAGS@
		
libortpextension_la_CPPFLAGS = \
		-I$(top_srcdir)/include \
		@ortp_CFLAGS@
		

