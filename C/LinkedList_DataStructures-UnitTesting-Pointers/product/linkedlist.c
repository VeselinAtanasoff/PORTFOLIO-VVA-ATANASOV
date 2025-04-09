/* SD exercise 1: simple linked list API */
/* Author : R. Frenken                   */
/* Version : 1.0			 */
#include "linkedlist.h"
#include <stdlib.h>

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise prepend a new ITEM with value value   */
/* to the existing list                            */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_first(ITEM **list, int value)
{
	/* Implement */

	ITEM *new_item = (ITEM *)malloc(sizeof(ITEM));
	if (new_item == NULL)
	{
		return -1;
	}

	new_item->value = value;
	new_item->next = *list;
	*list = new_item;

	return 0;
}

/***************************************************/
/* If *list == NULL, a new list should be created, */
/* otherwise append a new ITEM with value value to */
/* the existing list                               */
/* Returns -1 if not enough memory, otherwise 0    */
/***************************************************/

int add_last(ITEM **list, int value)
{
	/* Implement */
	ITEM *new_item = (ITEM *)malloc(sizeof(ITEM));
	if (new_item == NULL)
	{
		return -1;
	}

	new_item->value = value;
	new_item->next = NULL;

	if (*list == NULL)
	{
		*list = new_item;
	}
	else
	{
		ITEM *current = *list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_item;
	}

	return 0;
}

/****************************************************/
/* Insert a new item after current item c_item      */
/* Returns -1 if not enough memory, c_item == NULL, */
/* *list == NULL or c_item not found, otherwise 0   */
/****************************************************/

int add_after(ITEM *list, ITEM *c_item, int value)
{
	/* Implement */
	if (c_item == NULL || list == NULL)
	{
		return -1;
	}

	ITEM *new_item = (ITEM *)malloc(sizeof(ITEM));
	if (new_item == NULL)
	{
		return -1;
	}

	while(list != NULL)
	{
		if (list == c_item)
		{
			new_item->value = value;
			new_item->next = list->next;
			list->next = new_item;
			return 0;
		}
		list = list->next;

		if(list == NULL)
		{
			return -1;
		}
	}

	return 0;
}


/***************************************************/
/* Remove first item of the list                   */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/

int rem_first(ITEM **list)
{
	/* Implement */
	if (*list == NULL)
	{
		return -1;
	}

	ITEM *temp = *list;
	*list = (*list)->next;
	free(temp);

	return 0;
}

/***************************************************/
/* Remove last item of the list                    */
/* Returns -1 if list==NULL, otherwise 0           */
/***************************************************/


int rem_last(ITEM **list)
{
	/* Implement */
	if (*list == NULL)
	{
		return -1;
	}

	if((*list)->next == NULL)
	{
		free(*list);
		*list = NULL;
		return 0;
	}

	ITEM *current = *list;
	while(current->next->next != NULL)
	{
		current = current->next;
		

	}
	free(current->next);
	return 0;
}

/***************************************************/
/* Remove item after c_item of the list            */
/* Returns -1 list==NULL, c_item not found or      */
/* c_item is the last_element                      */
/***************************************************/

int rem_after(ITEM *list, ITEM *c_item)
{
	/* Implement */
	if (list == NULL || c_item == NULL)
	{
		return -1;
	}

	while(list != NULL)
	{
		if (list == c_item)
		{
			if (list->next == NULL)
			{
				return -1;
			}
			ITEM *temp = list->next;
			list->next = list->next->next;
			free(temp);
			return 0;
		}
		list = list->next;
	}
	return -1;
}

/*********************************************************/
/* All dynamic memory allocated to the list is freed     */
/* Empty list should point to NULL                       */
/*********************************************************/

void clean(ITEM **list)
{
	/* Implement */

	ITEM *current = *list;
	while(current != NULL)
	{
		ITEM *temp = current;
		current = current->next;
		free(temp);
	}
	
	return;
}

