#include "main.h"

/**
 * main - simple_shell's main routine
 * Return: 0 always
 */
int main(void)
{
	char *cmdline = NULL, *dirs/*, *set_envs[MAXARGS]*/;
	d_t *head = NULL;
	res _res = {-1, -1}, *res = &_res;
	int n_read, loop = 1;
	size_t len = 0;

	/*set_envs[0] = NULL;*/
	dirs = _getenv(environ, "PATH", res);/*get path directories*/
	create_path_list(dirs, &head);/*create a linked list of these directories*/
	free(dirs);
	Signal(SIGINT, sigint_handler);/*catch (CTRL + C)*/
	while (loop) /*only terminates if feof/builtin_command evaluates to true*/
	{
		/* Read cmd from stdin */
		/*write(1, "#cisfun$ ", 9);*/
		n_read = get_line(&cmdline, &len, STDIN_FILENO);
		if (n_read == -1)/*checks EOF status and exit if set*/
		{
			free_path_list(head);
			/*printf("past free-path-list\n");*/
			free(cmdline);
			/*printf("past free cmdline\n");*/
			exit(0);
		}
		/* Evaluate the cmd */
		evaluate_command_line(cmdline, head);
	}
	return (0);
}

