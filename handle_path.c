#include "main.h"

/**
 * add_node_end - adds a new node to the end of d_t list
 * @head: a pointer to the pointer to the head
 * @str: the new node's string
 * Return: pointer to the new node
 */
d_t *add_node_end(d_t **head, const char *str)
{
	d_t *new;
	d_t *last;

	new = malloc(sizeof(d_t));
	if (new == NULL)
		return (NULL);
	new->dir = _strdup_v2(str);
	if (*head == NULL)/*its an empty list*/
	{
		/*printf("in a null situation:\n");*/
		new->next = NULL;
		*head = new; /*new head*/
	}
	else
	{
		/*printf("null situation avoided\n");*/
		last = *head;
		/*printf("we have a last node!");*/
		for (; last->next != NULL; last = last->next)
			;/*loop stops at last node*/
		last->next = new;
		new->next = NULL; /*new last*/
	}
	return (new);
}

/**
 * create_path_list - get next directory and add it to list
 * @dir_str: pointer to remaining directories string
 * @head: pointer to head of list
 * Return: pointer to head(first node)
 */
d_t *create_path_list(char *dir_str, d_t **head)
{
	int i = 0, j = 0;
	char dir[PATH_S];

	for (; dir_str[i] != '\0'; i++)
	{
		if (dir_str[i] != ':')
			dir[j++] = dir_str[i];
		else
		{
			dir[j++] = '\0';
			j = 0;
			/*printf("dir: %s\n", dir);*/
			/*add dir as node to linked list*/
			add_node_end(head, dir);
			/*printf("test_node dir: %s\n", test->dir);add_node returns the head*/
		}
	}
	dir[j] = '\0';
	/*printf("dir: %s\n", dir);*/
	/*add last node to list*/
	add_node_end(head, dir);
	/*printf("last added dir: %s\n", dir);*/
	return (*head);
}

/**
 * traverse - traverses a d_t list directory, searching for a file
 * @curr_dir: directory to traverse
 * @file: executable to search for in directory
 * @found: a flag, is updated when the file is found
 * Return: Nothing, updates found and file;
 */
void traverse(char *curr_dir, char *file, int *found)
{
	DIR *dir;
	struct dirent *entry;
	char path[PATH_S];

	/*printf("%s\n", curr_dir);*/

	dir = opendir(curr_dir);
	if (dir == NULL)
	{
		/*printf("opening %s failed\n", curr_dir);*/
		perror("opendir ");
	}
	else
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] != '.')
			{
				_strcpy(path, curr_dir);
				_strcat(path, "/");
				_strcat(path, entry->d_name);
			}
			if (_strcmp(entry->d_name, file) == 0)
			{
				*found = 1;/*to get of loop*/
				/*printf("%s found in %s!\n", file, path);*/
				_strcpy(file, path);
				break;
			}
		}
		closedir(dir);
	}
}

/**
 * parse_path - searches for the executable in PATH
 * @head: the head_node to the path dirs_list to parse one after the other
 * @file: the file to look for in path
 * Return: complete pathname and NULL otherwise (null)
 */
char *parse_path(d_t **head, char *file)
{
	d_t *current;/*current node*/
	int found = 0;

	/*printf("found: %d", *found);*/
	for (current = *head; current != NULL && !found; current = current->next)
	{
		/*printf("traversing in %s\n", current->str);*/
		traverse(current->dir, file, &found);
	}
	/*printf("found: %d", *found);*/
	if (!found)
		file[0] = '\0';
	return (file);
}

/**
 * free_path_list - frees a d_t list
 * @head: a pointer to a d_t list
 * Return: Nothing
 */
void free_path_list(d_t *head)
{
	d_t *current;

	while (head != NULL)
	{
		current = head;
		head = head->next;
		free(current->dir);
		free(current);
	}

}
