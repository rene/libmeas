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
 * Functions for time measurement
 */
#include <meas.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/times.h>
#include <errno.h>

extern char _libmeas_use_syscall;

/**
 * static functions
 */
static unsigned long getjiffies(void);


/**
 * Start or/and create a timer
 * @param mst The meas user structure. This argument is necessary only in the first call to create the clock (second argument will be NULL). After that, you can just pass NULL to mst and pass the clock in second argument.
 * @param clock The clock created with this function. Use NULL in the first call.
 * @param name A name to the clock (useful for report visualization).
 * @return NULL if both mst and clock are different of NULL or the created clock.
 */
meas_clock *meas_start_clock(meas_t **mst, meas_clock *clock, char *name)
{
	meas_t *umst = *mst;
	meas_clock *ntimer;

	if(mst != NULL && clock == NULL) {
		if((ntimer = (meas_clock*)malloc(sizeof(meas_clock))) == NULL)
			return(NULL);

		ntimer->interv = 0;
		llist_add(&umst->timers, ntimer);
	} else if(mst == NULL && clock != NULL) {
		ntimer = clock;
	} else {
		return(NULL);
	}

	ntimer->state = TIMER_ST_RUNNING;
	ntimer->start_time = getjiffies();
	strcpy(ntimer->name, name);
	return(ntimer);
}


/**
 * Stop a timer
 * @param clock The timer
 * @return TRUE if the timer was stopped or FALSE if the timer was already stopped.
 */
int meas_stop_clock(meas_clock *clock)
{
	if(clock == NULL)
		return(FALSE);

	clock->state    = TIMER_ST_STOPPED;
	clock->end_time = getjiffies();
	clock->interv   = clock->end_time - clock->start_time;

	return(TRUE);
}


/**
 * Function to count clock ticks of the system
 * This function use the getjiffies() system call. The kernel needs to be
 * patched with getjiffies patch.
 * @return unsigned long
 */
static unsigned long getjiffies(void)
{
	unsigned long jiffies = 0;
	struct tms buf;

	if (_libmeas_use_syscall == 1) {
		jiffies = syscall(SYS_getjiffies);
		if (errno != 0) {
			fprintf(stderr, "libmeas CRITICAL ERROR: getjiffies()\n");
			return(0);
		}
	} else {
		jiffies = (unsigned long)times(&buf);
	}
	return(jiffies);
}

