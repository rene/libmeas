 /**
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

#ifndef MEAS_H

	#define MEAS_H

	#include <stdio.h>
	#include <config.h>
	#include <linkedl.h>
	#include <sys/time.h>
	#include <sys/resource.h>

	/**
	 * syscall getjiffies number
	 */
	#define SYS_getjiffies 500  //335 //337

	/**
	 * Max. size of a element name
	 */
	#define MAX_NAME_SIZE 35

	/**
	 * Timer states
	 */
	#define TIMER_ST_RUNNING 1
	#define TIMER_ST_STOPPED 0

	/**
	 * Counter states
 	 */
	#define COUNTER_ST_COUNTING 1
	#define COUNTER_ST_STOPPED  0

	/**
	 * Show timers in report
	 */
	#define REPORT_TIMERS		0x01

	/**
	 * Show counters in report
	 */
	#define REPORT_COUNTERS		0x02

	/**
	 * Show items added by user
	 */
	#define REPORT_USER_ITEMS 	0x04

	/**
	 * Show all parameters in report
	 */
	#define REPORT_SHOW_ALL (REPORT_TIMERS | REPORT_COUNTERS | REPORT_USER_ITEMS)


	/**
	 * Text Buffer
	 */
	struct _text_buffer {
		char *text;
		unsigned long size;
		unsigned long pos;
	};

	/**
	 * Report item
	 */
	struct _meas_report_item {
		char name[MAX_NAME_SIZE];
		char fmt[MAX_NAME_SIZE];
		long value;
	};

	/**
	 * Main structure
	 */
	struct _meas_t {
		llist *counters;
		llist *timers;
		struct rusage resources;
		llist *report_items;
		struct _text_buffer report;
	};

	/**
	 * Clock structure
	 */
	struct _meas_clock {
		int state;
		char name[MAX_NAME_SIZE];
		unsigned long start_time;
		unsigned long end_time;
		unsigned long interv;
	};

	/**
	 * Counter structure
	 */
	struct _meas_counter {
		int state;
		char name[MAX_NAME_SIZE];
		unsigned long value;
	};


	/**
	 * Typedefs
	 */
	typedef struct _meas_t       	 meas_t;
	typedef struct _meas_clock   	 meas_clock;
	typedef struct _meas_counter 	 meas_counter;
	typedef struct _meas_report_item meas_report_item;


	/**
	 * Meas functions
	 */
	int  meas_init(meas_t **mst);
	void meas_close(meas_t **mst);
	
	/**
 	 * Timer functions
	 */
	meas_clock *meas_start_clock(meas_t **mst, meas_clock *clock, char *name);
	int meas_stop_clock(meas_clock *clock);

	/**
	 * Counter functions
	 */
	meas_counter *meas_create_counter(meas_t **mst, unsigned long ivalue, char *name);
	unsigned long meas_set_counter(meas_counter *counter, unsigned long value);
	unsigned long meas_get_counter(meas_counter counter);
	unsigned long meas_inc_counter(meas_counter *counter);
	unsigned long meas_dec_counter(meas_counter *counter);

	/**
	 * Resources functions
	 */
	struct timeval *meas_get_utime(meas_t **mst, int who);
	struct timeval *meas_get_stime(meas_t **mst, int who);
	long meas_get_shared_mem(meas_t **mst, int who);
	long meas_get_datasec(meas_t **mst, int who);
	long meas_get_stack(meas_t **mst, int who);
	long meas_get_nswap(meas_t **mst, int who);
	long meas_get_nsignals(meas_t **mst, int who);
	long meas_get_blkinput(meas_t **mst, int who);
	long meas_get_blkoutput(meas_t **mst, int who);
	long meas_get_cswitches(meas_t **mst, int who);

	/**
	 * Report functions
	 */
	int meas_generate_report(meas_t **mst, int parameters);
	void meas_write_report(meas_t *mst, FILE *fp);
	int meas_add_report_item(meas_t **mst, char *name, char *fmt, long value);

#endif

