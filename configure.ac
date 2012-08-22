dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)

AC_INIT(ortpextension, 1.0)
AC_PROG_CC
AC_PROG_CXX
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([no])])

dnl Initialize automake
AM_INIT_AUTOMAKE([-Wall])

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Doxygen
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME],[ortpextension.doxyfile],[doc])

PKG_CHECK_MODULES(ortp, [ortp >= 0.17.0], , [
AC_MSG_RESULT(no)
AC_MSG_ERROR([

You must have ortp >= 0.17.0
])])

AC_SUBST(libnotify_CFLAGS)
AC_SUBST(libnotify_LIBS)

dnl Initialize Libtool
LT_INIT

dnl Check if Libtool is present
dnl Libtool is used for building share libraries 
AC_PROG_LIBTOOL

AC_CONFIG_FILES(
ortpextension.pc
Makefile
example/Makefile
src/Makefile
include/ortpextension/Makefile)
AC_OUTPUT