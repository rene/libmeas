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
 * Functions for report generation
 */
#include <meas.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * Size of text buffer
 */
#define TEXTBUFFER_SIZE 1024

/**
 * static functions
 */
static int append_text(struct _text_buffer *buffer, char *text);


/**
 * Generate report information.
 * NOTE1: The new report will replace any previous report generated.
 * NOTE2: This function will just generate the report, use meas_show_report
 *        to print it.
 * @param mst The meas user structure. 
 * @param parameters Parameters of report (REPORT_TIMERS, REPORT_COUNTERS or REPORT_SHOW_ALL).
 * @return FALSE on error, TRUE otherwise.
 */
int meas_generate_report(meas_t **mst, int parameters)
{
	meas_t *umst = *mst;
	meas_clock *clock;
	meas_counter *counter;
	meas_report_item *item;
	time_t curtime;
	char line[1024];
	int i, j, k;

	if(mst == NULL)
		return(FALSE);
	
	/* Header */
	append_text(&umst->report, "****************************************************************\n"); 
	append_text(&umst->report, "* libmeas - A measurement system for critical embedded systems *\n");
	append_text(&umst->report, "*                       ANALYSIS REPORT                        *\n");
	append_text(&umst->report, "****************************************************************\n\n");

	/* Generated information */
	time(&curtime);
	strftime(line, 1023, " Generated on %a %b %T %Y\n\n", localtime(&curtime));
	append_text(&umst->report, line);

	/* Timers */
	if ((parameters & REPORT_TIMERS)) {
		append_text(&umst->report, "============================ TIMERS ============================\n");
		append_text(&umst->report, " TIMER NAME                          NUMBER OF TICKS            \n");
		append_text(&umst->report, "================================================================\n");

		for (i = 0; i < llist_length(umst->timers); i++) {
			clock = (meas_clock*)llist_nth(umst->timers, i);
			if (clock != NULL) {
				sprintf(line, " %.35s", clock->name);
				append_text(&umst->report, line);
				for (k = 0; k < (MAX_NAME_SIZE - strlen(clock->name)); k++) {
					sprintf(line, " ");
					append_text(&umst->report, line);
				}
			 	sprintf(line, "   %ld\n", clock->interv);
				append_text(&umst->report, line);
			}
		}

		append_text(&umst->report, "----------------------------------------------------------------\n\n");
	}

	/* Counters */
	if ((parameters & REPORT_COUNTERS)) {
		append_text(&umst->report, "=========================== COUNTERS ===========================\n");
		append_text(&umst->report, " COUNTER NAME                         VALUE                     \n");
		append_text(&umst->report, "================================================================\n");

		for (j = 0; j < llist_length(umst->counters); j++) {
			counter = (meas_counter*)llist_nth(umst->counters, j);
			if (counter != NULL) {
				sprintf(line, " %.35s", counter->name);
				append_text(&umst->report, line);
				for (k = 0; k < (MAX_NAME_SIZE - strlen(counter->name)); k++) {
					sprintf(line, " ");
					append_text(&umst->report, line);
				}
				sprintf(line, "   %ld\n", meas_get_counter(*counter));
				append_text(&umst->report, line);
			}
		}

		append_text(&umst->report, "----------------------------------------------------------------\n\n");
	}

	/* User items */
	if ((parameters & REPORT_USER_ITEMS)) {
		append_text(&umst->report, "========================== USER ITEMS ==========================\n");
		append_text(&umst->report, " ITEM NAME                            VALUE                     \n");
		append_text(&umst->report, "================================================================\n");

		for (j = 0; j < llist_length(umst->report_items); j++) {
			item = (meas_report_item*)llist_nth(umst->report_items, j);
			if (item != NULL) {
				sprintf(line, " %.35s", item->name);
				append_text(&umst->report, line);
				for (k = 0; k < (MAX_NAME_SIZE - strlen(item->name)); k++) {
					sprintf(line, " ");
					append_text(&umst->report, line);
				}

				sprintf(line, item->fmt, item->value);
				append_text(&umst->report, line);
			}
		}

		append_text(&umst->report, "----------------------------------------------------------------\n\n");
	}

	return(TRUE);
}


/**
 * Write report to file descriptor.
 * @param mst The meas user structure. 
 * @param fp File descriptor pointer.
 */
void meas_write_report(meas_t *mst, FILE *fp)
{
	if (mst != NULL) {
		if (mst->report.text != NULL) {
			fprintf(fp, "%s", mst->report.text);
		}
	}
}


/**
 * Add a item to the report
 * @param name Item name.
 * @param fmt printf format style to print value (e.g. " %ld ").
 * @param value Item value.
 * @return int TRUE if item was added, FALSE on error.
 */
int meas_add_report_item(meas_t **mst, char *name, char *fmt, long value)
{
	meas_t *umst = *mst;
	meas_report_item *nitem;
	
	if (mst == NULL)
		return(FALSE);

	if ((nitem = (meas_report_item*)malloc(sizeof(meas_report_item))) == NULL )
		return(FALSE);


	strcpy(nitem->name, name);
	strcpy(nitem->fmt, fmt);
	nitem->value = value;

	llist_add(&umst->report_items, nitem);

	return(TRUE);
}


/**
 * Append text (with auto memory allocation) to the text buffer.
 * @param buffer The text buffer.
 * @param text The text to append.
 * @return TRUE if text was appended, FALSE otherwise.
 */
static int append_text(struct _text_buffer *buffer, char *text)
{
	size_t tsize;
	unsigned long free_ch, nblocks, iblocks;
	char *nbuffer;

	if(buffer == NULL)
		return(FALSE);

	tsize   = strlen(text);
	free_ch = buffer->size - buffer->pos;

	if (tsize >= free_ch) {
		nblocks = (buffer->size / TEXTBUFFER_SIZE) + 1;
		iblocks = ((tsize - free_ch) / TEXTBUFFER_SIZE) + 1;

		if((nbuffer = realloc(buffer->text, sizeof(char) * (TEXTBUFFER_SIZE * iblocks * nblocks))) == NULL) {
			return(FALSE);
		} else {
			buffer->text = nbuffer;
			buffer->size += (TEXTBUFFER_SIZE * iblocks);
		}
	}

	strcat(&buffer->text[buffer->pos], text);
	buffer->pos  += tsize;
	return(TRUE);
}

