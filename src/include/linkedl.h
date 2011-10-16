 /*
  * libmeas - A measurement system for critical embedded systems
  *
  * Copyright (C) 2009 Renê de Souza Pinto
  *
  * Original file from: TempOS project. http://tempos-project.org
  *
  * This file is part of libmeas
  *
  * libmeas is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.m
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
 * Linked list header
 */

#ifndef LLIST_H

	#define LLIST_H

	#include <config.h>
	#include <stdlib.h>

	#define foreach(list, tmp) for(tmp = list; tmp != NULL; tmp = tmp->next)


	/**
	 * Singly-linked list structure
	 */
	struct _llist {
		void *element;
		struct _llist *next;
	} __attribute__ ((packed));


	typedef struct _llist llist;


	int llist_create(llist **list);

	int llist_destroy(llist **list);

	int llist_add(llist **list, void *element);

	int llist_remove_nth(llist **list, unsigned int pos);

	int llist_remove(llist **list, void *element);

	void *llist_nth(llist *list, unsigned int index);

	int llist_index(llist *list, void *element);

	int llist_length(llist *list);

#endif /* LLIST_H */

