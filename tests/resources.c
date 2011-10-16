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
#include <stdlib.h>
#include <meas.h>


/*
 * Test - Use time measurement with sort functions
 */
int r_fibonacci(int x);
int nr_fibonacci(int x);


meas_t *mst;
meas_counter *c1, *c2;

/**
 * Main
 */
int main(int argc, char **argv)
{
	int v1, v2;
	meas_clock *t1, *t2;

	meas_init(&mst);

	c1 = meas_create_counter(&mst, 0, "C_REC");
	c2 = meas_create_counter(&mst, 0, "C_NONREC");


	/* Recursive version */
	t1 = meas_start_clock(&mst, NULL, "T_REC");
	v1 = r_fibonacci(35);
	meas_stop_clock(t1);

	/* Non recursive version */
	t2 = meas_start_clock(&mst, NULL, "T_NONREC");
	v2 = nr_fibonacci(35);
	meas_stop_clock(t2);

	meas_add_report_item(&mst, "REC_VALUE", "%d\n", v1);
	meas_add_report_item(&mst, "NONREC_VALUE", "%d\n", v2);

	meas_add_report_item(&mst, "N_SWAPS", "%d\n", meas_get_nswap(&mst, RUSAGE_SELF));
	meas_add_report_item(&mst, "N_CONTEXT_SWITCHES", "%d\n", meas_get_cswitches(&mst, RUSAGE_SELF));

	/* Generate and write report */
	meas_generate_report(&mst, REPORT_SHOW_ALL);
	meas_write_report(mst, stdout);

	meas_close(&mst);

	return(0);
}


/**
 * Generate Fibonacci number (recursive version)
 * @param n Position of the number at Fibobacci sequence.
 * @return int The Fibonacci sequence number.
 */
int r_fibonacci(int x)
{
	meas_inc_counter(c1);

	if (x == 0) {
		return(0);
	} else if (x == 1) {
		return(1);
	} else {
		return(r_fibonacci(x - 1) + r_fibonacci(x - 2));
	}
}


/** 
 * Generate Fibonacci number (non-recursive version)
 * @param n Position of the number at Fibobacci sequence.
 * @return int The Fibonacci sequence number.
 */
int nr_fibonacci(int x)
{
	int stack[40];
	int i, p;
	int s1, s2;

	stack[0] = 0; /* PUSH 0 */
	stack[1] = 1; /* PUSH 1 */

	i = x;
	p = 2;
	while(i >= 2) {
		meas_inc_counter(c2);

		s1 = stack[--p]; 		/* POP  s1 		  */
		s2 = stack[--p]; 		/* POP  s2 		  */
		stack[p++] = s2; 		/* PUSH s2 		  */
		stack[p++] = s1; 		/* PUSH s1 		  */
		stack[p++] = (s1 + s2); /* PUSH (s1 + s2) */
		i--;
	}
	return(stack[--p]);
}

