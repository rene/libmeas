##
# libmeas - A measurement system for critical embedded systems
#
# Copyright (C) 2009 Renê de Souza Pinto
#
# This file is part of libmeas
#
# libmeas is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libmeas is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
AC_INIT([libmeas], [0.1], [rene@renesp.com.br])
AC_CONFIG_AUX_DIR([build-aux/])
AM_INIT_AUTOMAKE([1.9 foreign])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_FILES([Makefile src/Makefile tests/Makefile])
AC_CONFIG_MACRO_DIR([m4])

# Check for programs
AC_PROG_CC
AC_PROG_LIBTOOL

######################################################################
# DOXYGEN SUPPORT
######################################################################

DX_DOXYGEN_FEATURE(ON)

DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(ON)
DX_PS_FEATURE(OFF)

DX_INIT_DOXYGEN([$PACKAGE_NAME],[doxygen.cfg],[doc])

######################################################################

# Check for headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h time.h unistd.h errno.h])
AC_CHECK_HEADERS([sys/syscall.h sys/time sys/resource])

# Define variables
AC_DEFINE([TRUE],  [1], [Boolean value for C functions])
AC_DEFINE([FALSE], [0], [Boolean value for C functions])

# Check for library functions
AC_FUNC_MALLOC

# Output
AC_OUTPUT

