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
 * @command: buffer contaiing formatted string
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
	}
	else if (argv[1][1] != '(')
	{
		argv[1][0] = '\0';
	}
	/* handle the situation where it's a command! - that's the else */
}

/**
 * _cd - cd implementation using chdir and getcwd
 * @av: command line arguments array
 * @status: pointer to exit_status flag
 * Return: 0 on success and -1 otherwise
 */
int _cd(char **av, int *status)
{
	res a_res = {-1, -1}, *res = &a_res;
	char *pathname, _pwd[MAXLINE]; /*buf[PATH_S];*/
	int success = 0;

	getcwd(_pwd, MAXLINE);/*get current working directory*/
	if (av[1] == NULL)/*only one arg, cd - go back $home*/
	{
		pathname = _getenv(environ, "HOME", res);
		if (pathname)
			chdir(pathname);
		else
			unix_error("_getenv error");
	}
	else if (_strcmp(av[1], "-") == 0)
	{
		pathname = _getenv(environ, "OLDPWD", res);
		if (pathname)
		{
			printf("%s\n", pathname);
			chdir(pathname);
		}
		else
			unix_error("_getenv error");
	}
	else
	{
		pathname = av[1];
		if (chdir(pathname))/*returns -1 on error and 0 on success*/
		{
			set_success(1);
			unix_error("cd");
			success = 1;/*failed*/
		}
	}
	/*reset oldpwd's value to current pwd*/
	_setenv("OLDPWD", _pwd, 1);
	*status = success;/*success or failure*/
	/*change environ's pwd to pathname*/
	return (_setenv("PWD", pathname, 1));/*0 on success and -1 on failure*/
}

/**
 * builtin_command - check if argv[0] is a built-in cmd
 * & update exit_status if true (on execution)
 * @argv: the command(line) as **argv, array of strings
 * @status: exit_status flag
 * Return: 1 if true and 0 otherwise
 */
int builtin_command(char **argv, int *status)
{
	int i = 0;
	char buf[MAXLINE];

	if (!_strcmp(argv[0], "exit"))/*i.e if command is exit*/
	{
		if (argv[1])
			exit(atoi(argv[1]));/*handle exit argument/status*/
		exit(0);/*terminate process*/
	}
	if (!_strcmp(argv[0], "alias"))/*i.e if command is exit*/
	{
		_alias(argv, status);/*handle alias*/
		return (1);
	}
	if (!_strcmp(argv[0], "env"))/*i.e if command is env*/
	{
		/*print environ*/
		for (; environ[i] != NULL; i++)
			_write(buf, environ[i], "\n");
		/*printf("%s\n", environ[i]);*/
		*status = 0;/*successful*/
		return (1);/*i.e return true - builtin command*/
	}
	if (!_strcmp(argv[0], "cd"))/*i.e if command is exit*/
	{
		return (!_cd(argv, status));
	}
	if (!_strcmp(argv[0], "setenv") || !_strcmp(argv[0], "unsetenv"))
	{
		if (!_strcmp(argv[0], "setenv"))
			i = _setenv(argv[1], argv[2], 1);/*setenv VARIABLE VALUE overwrite*/
		else
			i = _unsetenv(argv[1]);/*unsetenv VARIABLE*/
		*status = i;/*successful*/
		return (!i);
	}
	if (!_strcmp(argv[0], "&")) /*ignore singleton &*/
		return (1);
	return (0); /*i.e. not a built in command*/
}


