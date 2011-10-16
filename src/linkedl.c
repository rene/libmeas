 /*
  * libmeas - A measurement system for critical embedded systems
  *
  * Copyright (C) 2009 Renê de Souza Pinto
  *
  * Original file from: TempOS project. http://tempos-project.org
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
 * Linked list functions
 * For libmeas internal use.
 */

#include <linkedl.h>


/**
 * Create a empty linked list
 * @param list Pointer to list
 * @return FALSE on error. TRUE otherwise
 */
int llist_create(llist **list)
{
	*list = NULL;
	return(TRUE);
}


/**
 * Destroy a linked list (remove all items)
 * @param list Pointer to list
 * @return FALSE on error. TRUE otherwise
 */
int llist_destroy(llist **list)
{
	llist *tmp = *list;

	if(tmp != NULL) {
		llist_destroy(&tmp->next);
		if (tmp->element != NULL) {
			free(tmp->element);
		}
		free(tmp);
		tmp = NULL;
	}

	return(TRUE);
}


/**
 * Add item to the list
 * @param list Pointer to the list
 * @param element Any element (void pointer)
 * @return FALSE on error. TRUE otherwise
 */
int llist_add(llist **list, void *element)
{
	llist *rlist = *list;
	llist *new_node, *tmp, *prev;

	new_node = (llist*)malloc(sizeof(llist));
	if(new_node == NULL) {
		return(FALSE);
	} else {
		new_node->element = element;
		new_node->next    = NULL;
	}

	if(rlist == NULL) {
		/* First element */
		rlist = new_node;
	} else {
		/* Add to the end */
		for(tmp = prev = rlist; tmp != NULL;
				prev = tmp, tmp = tmp->next);

		if(prev != NULL)
			prev->next = new_node;
	}

	*list = rlist;
	return(TRUE);
}


/**
 * Remove the nth item of the list
 * @param list Pointer to the list
 * @param pos Item position at the list
 * @return FALSE on error. TRUE otherwise
 */
int llist_remove_nth(llist **list, unsigned int pos)
{
	llist *rlist = *list;
	llist *tmp, *prev;
	unsigned int p;

	/* Remove first element */
	if(pos == 0) {
		tmp   = rlist;
		rlist = rlist->next;
		free(tmp);
		*list = rlist;
		return(TRUE);
	}

	/* Remove element */
	for(tmp = prev = rlist, p = 0; tmp != NULL && p < pos;
			p++, prev = tmp, tmp = tmp->next);

	if(prev != NULL) {
		if(tmp != NULL) {
			prev->next = tmp->next;
			free(tmp);
		} else {

		}
		*list = rlist;
		return(TRUE);
	} else {
		return(FALSE);
	}
}


/**
 * Remove an item from the list
 * @param list Pointer to the list
 * @param element Pointer to the item to be removed
 * @return FALSE on error. TRUE otherwise
 */
int llist_remove(llist **list, void *element)
{
	llist *rlist = *list;
	llist *tmp, *prev;

	if(rlist == NULL)
		return(FALSE);

	/* Remove first element */
	if(rlist->element == element) {
		tmp   = rlist;
		rlist = rlist->next;
		free(tmp);
		*list = rlist;
		return(TRUE);
	}

	/* Remove element */
	for(tmp = prev = rlist; tmp != NULL;
			prev = tmp, tmp = tmp->next) {
		if(tmp->element == element) {
			break;
		}
	}

	if(tmp != NULL && prev != NULL) {
		prev->next = tmp->next;
		free(tmp);
		*list = rlist;
		return(TRUE);
	} else {
		return(FALSE);
	}
}


/**
 * Return the nth element of the list
 * @param list List
 * @param index Element position
 * @return void* Pointer to the element or NULL if not found
 */
void *llist_nth(llist *list, unsigned int index)
{
	llist *tmp = list;
	unsigned int p;

	for(tmp = list, p = 0; tmp != NULL && p < index;
			p++, tmp = tmp->next);

	if(tmp != NULL) {
		return(tmp->element);
	} else {
		return(NULL);
	}
}


/**
 * Return the index of some element list
 * @param list List
 * @param element Item
 * @return Element index or -1 (if not found)
 */
int llist_index(llist *list, void *element)
{
	llist *tmp;
	int p;

	if(list == NULL)
		return(-1);

	/* First element */
	if(list->element == element) {
		return(FALSE);
	}

	/* Search in list */
	for(tmp = list, p = 0; tmp != NULL; p++, tmp = tmp->next) {
		if(tmp->element == element) {
			break;
		}
	}

	if(tmp != NULL) {
		return(p);
	} else {
		return(-1);
	}
}


/**
 * Return the number of items inside the list
 * @param list List
 * @return The number of items
 */
int llist_length(llist *list)
{
	llist *tmp   = list;
	int size = 0;

	while(tmp != NULL) {
		size++;
		tmp = tmp->next;
	}

	return(size);
}


