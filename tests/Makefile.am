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

AM_CFLAGS = -Wall

INCLUDES = -I$(top_srcdir) -I$(top_srcdir)/src/include

TESTS = sorts loops resources

bin_PROGRAMS  = sorts loops resources

sorts_SOURCES = sorts.c
sorts_LDADD   = $(top_srcdir)/src/.libs/libmeas.a

loops_SOURCES = loops.c
loops_LDADD   = $(top_srcdir)/src/.libs/libmeas.a

resources_SOURCES = resources.c
resources_LDADD   = $(top_srcdir)/src/.libs/libmeas.a

