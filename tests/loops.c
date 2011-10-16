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

#include <stdio.h>
#include <meas.h>

/*
 * Test - Use counter measurement
 */

#define LOOP1 100
#define LOOP2  50


/**
 * Main
 */
int main(int argc, char **argv)
{
	int i, j;
	meas_t *mst;
	meas_counter *ct1, *ct2;

	meas_init(&mst);

	ct1 = meas_create_counter(&mst, 0, "counter_loop1");

	for (i = 0; i < LOOP1; i++) {
		meas_inc_counter(ct1);
	}

	ct2 = meas_create_counter(&mst, LOOP2, "counter_loop2");

	j = LOOP2;
	while(j >= 0) {
		meas_dec_counter(ct2);
		j--;
	}

	/* Generate report */
	meas_generate_report(&mst, REPORT_COUNTERS);
	meas_write_report(mst, stdout);

	meas_close(&mst);
	return(0);
}

