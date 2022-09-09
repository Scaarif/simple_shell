#include "main.h"


/**
 * _alias - an implementation of alias()
 * @argv: pointer to array of args
 * @status: pointer to exit_status flag
 * Return: ALIAS array? (in env)
 */
void _alias(char **argv, int *status)
{
	(void)argv;
	*status = 0;
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
	char *pathname, _pwd[MAXLINE], _pathname[PATH_S], *path; /*buf[PATH_S];*/
	int success = 0;

	getcwd(_pwd, MAXLINE);/*get current working directory*/
	if (av[1] == NULL)/*only one arg, cd - go back $home*/
	{
		_strcpy(_pathname, (pathname = _getenv(environ, "HOME", res)));
		if (_pathname != NULL)
			chdir(_pathname);
		else
			unix_error("_getenv error");
		free(pathname);
	}
	else if (_strcmp(av[1], "-") == 0)
	{
		_strcpy(_pathname, (pathname = _getenv(environ, "OLDPWD", res)));
		if (_pathname != NULL)
		{
			printf("%s\n", _pathname);
			chdir(_pathname);
		}
		else
			unix_error("_getenv error");
		free(pathname);
	}
	else
	{
		_strcpy(_pathname, (path = av[1]));
		if (chdir(path))/*returns -1 on error and 0 on success*/
		{
			unix_error("cd");
			success = 1;/*failed*/
		}
	}
	_setenv("OLDPWD", _pwd, 1);/*reset oldpwd's value to current pwd*/
	*status = success;/*success or failure*/
	_setenv("PWD", _pathname, 1);/*change environ's pwd to pathname*/
	return (success);/*0 on success and -1 on failure*/
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
