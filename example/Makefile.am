#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=exampleProgram

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=rtpextsend rtpextrecv

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 

rtpextsend_SOURCES= rtpextsend.c
rtpextrecv_SOURCES= rtpextrecv.c

# Linker options for a.out
rtpextsend_LDFLAGS = $(top_srcdir)/src/libortpextension.la \
		@ortp_LIBS@
rtpextrecv_LDFLAGS = $(top_srcdir)/src/libortpextension.la\
		@ortp_LIBS@

# Compiler options for a.out
rtpextsend_CFLAGS = -I$(top_srcdir)/include\
		@ortp_CFLAGS@
rtpextrecv_CFLAGS = -I$(top_srcdir)/include\
		@ortp_CFLAGS@

rtpextsend_CPPFLAGS = -I$(top_srcdir)/include\
		@ortp_CFLAGS@
rtpextrecv_CPPFLAGS = -I$(top_srcdir)/include\
		@ortp_CFLAGS@
