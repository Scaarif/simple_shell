#include "main.h"

/**
 * print_pathlist - prints the PATH linked list
 * @head: the list's head
 * Return: Nothing
 */
void print_pathlist(d_t **head)
{
	d_t *curr;
	char buf[PATH_S];

	for (curr = *head; curr != NULL; curr = curr->next)
		_write(buf, curr->dir, "\n");/*print dirs*/
}


/**
 * add_node - adds a new node to tail of list
 * @dir: the directory to add as node to list
 * @head: pointer to last list node
 * Return: pointer to head of path list
 */
d_t *add_node(char *dir, d_t **head)
{
	d_t *new_node, *tail;

	new_node = malloc(sizeof(d_t));
	if (new_node == NULL)
	{
		unix_error("malloc error");
		return (NULL);
	}
	/*printf("Add dir: %s\n", dir);*/
	new_node->dir = _strdup(dir);
	/*printf("added dir: %s\n", new_node->dir);*/
	tail = *head;
	if (tail == NULL)
	{
		new_node->next = tail;
		*head = new_node;/*update head*/
		/*if (*head == NULL)*/
			/*printf("head isn't updating!\n");*/
		/*else*/
			/*printf("updated head dir: %s\n", (*head)->dir);*/
		/*printf("NULL tail\n");*/
	}
	else
	{
		/*printf("tail dir: %s\n", tail->dir);*/
		for (; tail->next != NULL; tail = tail->next)
			;
		new_node->next = NULL;
		tail->next = new_node;/*new tail*/
		/*tail = new_node;*/
	}
	return (*head);
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
			add_node(dir, head);
			/*printf("test_node dir: %s\n", test->dir);add_node returns the head*/
		}
	}
	dir[j] = '\0';
	/*printf("dir: %s\n", dir);*/
	/*add last node to list*/
	add_node(dir, head);
	/*printf("last added dir: %s\n", dir);*/
	return (*head);
}

/**
 * parse_path - searches for the executable in PATH
 * @head: the head_node to the path dirs_list to parse one after the other
 * @file: the file to look for in path
 * Return: complete pathname and NULL otherwise
 */
char *parse_path(d_t **head, char *file)
{
	d_t *curr = *head;/*current node*/
	DIR *d_stream;
	struct dirent *d_entry;
	int i = 0, j = 0;

	/*for directories in list, get current directory*/
	for (; curr != NULL; curr = curr->next)
	{
		/*get a list of entries in the current directory*/
		d_stream = opendir(curr->dir);
		if (d_stream)
		{
			errno = 0;/*track to differentiate an error from end of stream*/
			while ((d_entry = readdir(d_stream)) != NULL)
			{/*get next entry/file in current_directory & compare with file*/
				if (_strcmp(d_entry->d_name, file) == 0)
				{
					for (; (file[i] = (curr->dir)[i]) != '\0'; i++)
						;
					file[i++] = '/';
					for (; (file[i] = (d_entry->d_name)[j]) != '\0'; i++, j++)
						;
					file[i] = '\0';
					return (file);/*return file in path*/
				}
			}
			if (errno != 0)
				unix_error("readdir error");
			closedir(d_stream);
		}
		/*else unix_error("opendir error");*/
	}
	return (NULL);/*file not in path*/
}
