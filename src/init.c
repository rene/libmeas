 /*
  * libmeas - A measurement system for critical embedded systems
  *
  * Copyright (C) 2009 Renê de Souza Pinto
  *
  * This file is part of libmeas
  *
  * libmeas is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * libmeas is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

/*
 * Initializer functions
 */

#include <meas.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>


char _libmeas_use_syscall = 0;

/**
 * Global constructor for libmeas internal allocation
 */
__attribute__((constructor)) void init(void)
{
	/*  Check if libmeas syscall is available */
	syscall(SYS_getjiffies);
	if(errno == 0) {
		/* It is, use it! */
		_libmeas_use_syscall = 1;
	} else {
		/* Not available */
		_libmeas_use_syscall = 0;
	}
}


/**
 * Global destructor for libmeas internal deallocation
 */
__attribute__((destructor)) void destroy(void)
{
	; /* Do nothing yet */
}


/**
 * Initialize user structures for use libmeas API
 * @param mst The user libmeas structure
 * @return int FALSE on error. True otherwhise
 * @see meas_close
 */
int meas_init(meas_t **mst)
{
	meas_t *umst = *mst;

	if((umst = (meas_t*)malloc(sizeof(meas_t))) == NULL) {
		return(FALSE);
	}

	llist_create(&umst->counters);
	llist_create(&umst->timers);
	llist_create(&umst->report_items);
	umst->report.text = NULL;
	umst->report.size = 0;
	umst->report.pos  = 0;

	*mst = umst;
	return(TRUE);
}


/**
 * Destroy libmeas user structures
 * @param mst The user libmeas structure
 * @see meas_init
 */
void meas_close(meas_t **mst)
{
	meas_t *umst = *mst;

	llist_destroy(&umst->counters);
	llist_destroy(&umst->timers);
	llist_destroy(&umst->report_items);
	if (umst->report.text != NULL) {
		free(umst->report.text);
	}

	free(umst);
	return;
}

