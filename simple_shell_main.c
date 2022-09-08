#include "main.h"

/**
 * main - simple_shell's main routine
 * Return: 0 always
 */
int main(void)
{
	char *cmdline = NULL, *dirs; /*the command(line) and PATH directories*/
	d_t *head = NULL;
	res _res = {-1, -1}, *res = &_res;
	int n_read;
	size_t len = 0;

	Signal(SIGINT, sigint_handler);/*catch (CTRL + C)*/
	dirs = _getenv(environ, "PATH", res);/*get path directories*/
	create_path_list(dirs, &head);/*create a linked list of these directories*/
	while (1) /*only terminates if feof/builtin_command evaluates to true*/
	{
		/* Read cmd from stdin */
		/*write(1, "#cisfun$ ", 9);*/
		/*Fgets(cmdline, MAXLINE, stdin);*/
		n_read = get_line(&cmdline, &len, STDIN_FILENO);
		if (n_read == -1)/*checks EOF status and exit if set*/
		{
			/*write(1, "\n", 1);*/
			exit(0);
		}
		/* Evaluate the cmd */
		evaluate_command_line(cmdline, head);
	}
}
