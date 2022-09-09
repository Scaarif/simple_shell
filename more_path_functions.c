#include "main.h"

/**
 * print_pathlist - prints all the elements of a d_t list
 * @h: a pointer to a d_t list
 * Description: prints [0] (nil) if str is NULL
 * Return: size_t number of nodes in list
 */
size_t print_pathlist(d_t *h)
{
	size_t len = 0;
	char buf[PATH_S];
	const d_t *current;

	for (current = h; current != NULL; len++, current = current->next)
	{
		if (current->dir == NULL)
			_write(buf, "(nil)", "\n");/*print dirs*/

		else
			_write(buf, current->dir, "\n");/*print dirs*/
	}
	return (len);
}
