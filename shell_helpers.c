#include "main.h"

/**
 * handle_comments - remove part of command-line
 * after #, the start of a comment
 * @buf: pointer to command-line
 * Return: pointer to buf
 */
char *handle_comments(char *buf)
{
	int i = 0;

	for (; buf[i] != '\0' && buf[i] != '#'; i++)
		;
	if (buf[i] == '#')
	{
		buf[i++] = '\n';
		buf[i] = '\0';/*terminate there*/
	}
	return (buf);
}

/**
 * format_command - include a new line and terminate
 * @cmd: the command string to parse
 * @command: buffer to contain formatted string
 * Return: pointer to buffer
 */
char *format_command(char *cmd, char *command)
{
	int k;

	for (k = 0; (command[k] = cmd[k]) != '\0'; k++)
		;
	command[k++] = '\n';
	command[k] = '\0'; /*terminate command*/
	return (command);
}

/**
 * check_for_delims - check for delimeters in commandline
 * @cmdline: the command_line
 * @delims: the delims to check for
 * @res: an array of the delims in cmdline
 * Return: a string of delimiters found
 */
char *check_for_delims(char *cmdline, char *delims, char *res)
{
	int i = 0, j = 0, k = 0;

	for (; delims[i] != '\0'; i++)
	{
		for (j = 0; cmdline[j] != '\0'; j++)
		{
			if (delims[i] == cmdline[j])
			{
				res[k++] = cmdline[j];
				break;
			}
			/*printf("char: %c\n",cmdline[j]);*/
		}
		/*printf("delim checked: %c\n", delims[i]);*/
	}
	res[k] = '\0';/*terminate it*/
	return (res);
}

/**
 * variable_substitute - implement variable replacement
 * & update exit status
 * @argv: pointer to command args
 * @status: exit status flag
 * Return: Nothing
 */
void variable_substitute(char **argv, int *status)
{
	int i = 0;
	char buf[20], *var, name[100];
	res _res = {-1, -1}, *res = &_res;

	/* handle env values, ppid and exit status*/
	if (argv[1][1] == '$')
	{
		_ltoa((long)getpid(), buf, 10);
		for (; (argv[1][i] = buf[i]) != '\0'; i++)
			;
		argv[1][i] = '\0';/*update argv[1] to pid_str*/
	}
	else if (argv[1][1] == '?')
	{
		_ltoa((long)*status, buf, 10);
		for (; (argv[1][i] = buf[i]) != '\0'; i++)
			;
		argv[1][i] = '\0';/*update argv[1] to exit_status*/
	}
	else if (argv[1][1] >= 'A' && argv[1][1] <= 'Z')
	{/* probably an env variable, so check */
		for (; (name[i] = argv[1][i + 1]) != '\0'; i++)
			;
		name[i] = '\0';/*terminate*/
		var = _getenv(environ, name, res);
		if (var)
		{
			for (i = 0; (argv[1][i] = var[i]) != '\0'; i++)
				;
			argv[1][i] = '\0';
		}
		else
			argv[1][0] = '\0';/*should be NULL*/
		free(var);/*malloc'd in _getenv*/
	}
	else if (argv[1][1] != '(')
	{
		argv[1][0] = '\0';
	}
	/* handle the situation where it's a command! - that's the else */
}
