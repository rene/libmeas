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

#define WORST_CASE  0
#define RANDOM_CASE 1

#define T1_SIZE 18000
#define T2_SIZE 18000


/*
 * Test - Use time measurement with sort functions
 */

int *create_v(int mode, int size);
void bubble(int *v, int size);
void heapsort(int a[], int n);


/**
 * Main
 */
int main(int argc, char **argv)
{
	int *t1;
	int *t2;
	meas_t *mst;
	meas_clock *timer1, *timer2;

	meas_init(&mst);

	/* Create vectors */
	t1 = create_v(WORST_CASE,  T1_SIZE);
	t2 = create_v(WORST_CASE, T2_SIZE);

	if(t1 == NULL || t2 == NULL)
		return(1);

	/* Sort */
	timer1 = meas_start_clock(&mst, NULL, "TIMER_BUBBLE");
	bubble(t1, T1_SIZE);
	meas_stop_clock(timer1);

	timer2 = meas_start_clock(&mst, NULL, "TIMER_HEAP");
	heapsort(t2, T2_SIZE);
	meas_stop_clock(timer2);

	/* Generate and write report */
	meas_generate_report(&mst, REPORT_TIMERS);
	meas_write_report(mst, stdout);

	meas_close(&mst);

	return(0);
}


/**
 * create integer vectors
 * @param mode WORST_CASE: elements from END to BEGIN | RANDOM_CASE: random elements
 * @param size Size of the vector
 * @return int* The created vector
 */
int *create_v(int mode, int size)
{
	int i;
	int *v;

	srand((unsigned int)time(NULL));

	if( (v = (int*)malloc(sizeof(int) * size)) == NULL)
		return(NULL);

	if(mode == WORST_CASE) {
		for(i=size-1; i>=0; i--)
			v[size-1-i] = i;
	} else if(mode == RANDOM_CASE) {
		for(i=0; i<size; i++) {
			v[i] = (rand() / RAND_MAX) * size;
		}
	}

	return(v);
}


/**
 * The bubble sort function
 * @param a Vetor to be sorted
 * @param size Size of the vector
 */
void bubble(int *v, int size)
{
	int i, j, temp;

	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			if(v[i] < v[j]) {
				temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}
	}
}


/**
 * The heap sort function
 * Code from: http://pt.wikipedia.org/wiki/Heapsort
 * @param a Vetor to be sorted
 * @param size Size of the vector
 */
void heapsort(int a[], int n)
{
   int i = n/2, pai, filho;
   int t;
 
   for (;;)
   {
      if (i > 0)
      {
          i--;
          t = a[i];
      }
      else
      {
          n--;
          if (n == 0)
             return;
          t = a[n];
          a[n] = a[0];
      }
     
      pai = i;
      filho = i*2 + 1;
 
      while (filho < n)
      {
          if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
              filho++;
          if (a[filho] > t)
          {
             a[pai] = a[filho];
             pai = filho;
             filho = pai*2 + 1;
          }
          else
             break;
      }
      a[pai] = t;
   }
}

