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
 * Counters
 */
#include <meas.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

/**
 * Create a counter
 * @param mst The meas user structure. 
 * @param ivalue Initial value.
 * @param name A name to the counter (useful for report visualization).
 * @return NULL on error or the created counter.
 */
meas_counter *meas_create_counter(meas_t **mst, unsigned long ivalue, char *name)
{
	meas_t *umst = *mst;
	meas_counter *ncounter;

	if(mst != NULL) {
		if((ncounter = (meas_counter*)malloc(sizeof(meas_counter))) == NULL)
			return(NULL);

		llist_add(&umst->counters, ncounter);
	} else {
		return(NULL);
	}

	ncounter->value = ivalue;
	strcpy(ncounter->name, name);
	return(ncounter);
}


/**
 * Set the value of a counter.
 * Use ONLY for change initial value.
 * @param counter The counter
 * @param value Value of the counter
 * @return unsigned long New value of the counter
 */
unsigned long meas_set_counter(meas_counter *counter, unsigned long value)
{
	if(counter != NULL) {
		counter->value = value;
		return(value);
	} else {
		return(0);
	}
}


/**
 * Return the value of a counter
 * @param counter The counter
 * @return unsigned long Value of the counter
 */
unsigned long meas_get_counter(meas_counter counter)
{
	return(counter.value);
}


/**
 * Increment the value of a counter
 * @param counter The counter
 * @return unsigned long New value of the counter
 */
unsigned long meas_inc_counter(meas_counter *counter)
{
	if (counter != NULL) {
		counter->value++;
	}
	return(counter->value);
}


/**
 * Increment the value of a counter
 * @param counter The counter
 * @return unsigned long New value of the counter
 */
unsigned long meas_dec_counter(meas_counter *counter)
{
	if (counter != NULL) {
		counter->value--;
	}
	return(counter->value);
}

