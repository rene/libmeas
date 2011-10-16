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
 * Functions for resources measurement
 */
#include <meas.h>


/**
 * Return the user time used
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return struct timeval NULL on error or amount of time that this process has been scheduled in user  mode,  measured in  clock  ticks (divide by sysconf(_SC_CLK_TCK).
 */
struct timeval *meas_get_utime(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(NULL);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(NULL);

	return(&umst->resources.ru_utime);
}


/**
 * Return the system time used
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return struct timeval NULL on error or amount of time that this process has been scheduled in kernel mode, measured in clock ticks (divide by sysconf(_SC_CLK_TCK).
 */
struct timeval *meas_get_stime(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(NULL);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(NULL);

	return(&umst->resources.ru_stime);
}


/**
 * Return the integral shared memory size
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or integral shared memory size.
 */
long meas_get_shared_mem(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_ixrss);
}


/**
 * Return the integral (unshared) data section size
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or integral (unshared) data section size.
 */
long meas_get_datasec(meas_t **mst, int who)
{
	meas_t *umst = *mst;
	
	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_idrss);
}


/**
 * Return the integral (unshared) stack size
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or integral (unshared) stack size.
 */
long meas_get_stack(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_isrss);
}


/**
 * Return the number of page faults
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of page faults.
 */
long meas_get_pagefault(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_majflt);
}


/**
 * Return the number of pages swapped
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of pages swapped.
 */
long meas_get_nswap(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_nswap);
}


/**
 * Return the number of signals received
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of signals received.
 */
long meas_get_nsignals(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_nsignals);
}


/**
 * Return the number of block input operations
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of block input operations.
 */
long meas_get_blkinput(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_inblock);
}


/**
 * Return the number of block output operations
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of block output operations.
 */
long meas_get_blkoutput(meas_t **mst, int who)
{
	meas_t *umst = *mst;
	
	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_oublock);
}


/**
 * Return the number context switches (voluntary + involuntary)
 * @param mst The meas user structure.
 * @param who Can be: RUSAGE_SELF (calling proccess), RUSAGE_CHILDREN (all children) or RUSAGE_THREAD (calling thread).
 * @return long -1 on error or number of total context switches.
 */
long meas_get_cswitches(meas_t **mst, int who)
{
	meas_t *umst = *mst;

	if (umst == NULL)
		return(-1);

	/* Update resources usage information */
	if(getrusage(who, &umst->resources) < 0)
		return(-1);

	return(umst->resources.ru_nvcsw + umst->resources.ru_nivcsw);
}

