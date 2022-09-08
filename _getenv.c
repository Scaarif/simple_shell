#include "main.h"

/**
 * get_name - return name, if available in env array
 * @_res: the res
 * @name_: the name to look for
 * @env: the env array to search from
 * Return: positive int(pos of last char) if name if found, 0 otherwise
 */

int get_name(char **env, char *name_, res *_res)
{
	char *var, *name;/*buf[PATH_S];*/
	int i = 0, j, len;

	for (; env[i] != NULL; i++)
	{
		var = env[i];
		j = 0;
		for (; var[j] != '='; j++)
			;
		name = malloc(sizeof(char) * j + 1);
		if (name == NULL)
			unix_error("malloc error");
		len = j;
		for (j = 0; j < len; j++)
			name[j] = var[j];
		name[j] = '\0';
		/*printf("char at len: %c & len + 1 %c\n", var[len], var[len + 1]);*/
		if (_strcmp(name_, name) == 0)
		{
			_res->var_index = i;
			_res->val_index = len + 1;/*skip the = sign*/
			free(name);/*free name, we dont need it*/
			return (_res->var_index);/*index of variable with name*/
		}
		else
			free(name);
	}
	/*_write(buf, name_, ": NOT FOUND\n");*/
	return (0);
}

/**
 * _getenv - returns the value of an environment variable
 * if name is found in env
 * @env: the env array to search from
 * @_res: the res
 * @name: the variable name whose value to get
 * Return: pointer to value if OK and NULL otherwise
 */
char *_getenv(char **env, char *name, res *_res)
{
	char *value, *var;
	int i = get_name(env, name, _res), len, j, val_idx;

	if (i != -1 && i)/*i is not -1 or 0*/
	{
		var = env[i];/*the relevant variable*/
		for (j = _res->val_index; var[j] != '\0'; j++)
			;
		len = j - _res->val_index;
		value = malloc(sizeof(char) * len + 1);
		/*printf("char at len + 1: %c\n", var[len_ + 1]);*/
		if (value == NULL)
			unix_error("malloc error");
		val_idx = _res->val_index;
		for (j = 0; j < len; j++)
		{
			value[j] = var[val_idx + j];
			/*printf("%c", value[j]);*/
		}
		value[j] = '\0';
		/*printf("fn value: %s\n", value);*/
		return (value);
	}
	return (NULL);
}

/**
 * new_variable - builds a new variable
 * @name: name of variable
 * @value: value of variable
 * Return: pointer to new variable
 */

char *new_variable(const char *name, const char *value)
{
	char *var, *name_ = (char *)name, *value_ = (char *)value;
	int i, j;

	var = malloc(sizeof(char) * (_strlen(name_) + _strlen(value_) + 2));
	if (var == NULL)
	{
		unix_error("malloc error");
		return (NULL);
	}
	/*fill up the values*/
	for (i = 0; name[i] != '\0'; i++)
		var[i] = name[i];
	var[i] = '=';
	for (++i, j = 0; value[j] != '\0'; j++, i++)
		var[i] = value[j];
	var[i] = '\0';/*terminate variable*/
	return (var);
}

/**
 * _setenv - adds an environment variable to environ if
 * it does not exist or changes it value to new value if one exits
 * @name: name of the variable
 * @value: the value of variable
 * @overwrite: non zero int to allow overwrite of value
 * and 0 to disallow
 * Return: 0 on success and -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	/*set var <name> to <value> if it exists; else create a new one*/
	res res = {-1, -1}, *a_res = &res;
	char *old_value;
	int exists = get_name(environ, (char *)name, a_res), i;

	if (exists != -1 && exists && overwrite)
	{
		old_value = _getenv(environ, (char *)name, a_res);
		if (_strlen(old_value) >= _strlen((char *)value))
		{
			/*replace old value with new*/
			for (i = 0; value[i] != '\0'; i++)
				environ[exists][a_res->val_index + i] = value[i];
			environ[exists][a_res->val_index + i] = '\0';
			/*free(old_value);malloc'd in _getenv*/
		}
		else
		{
			old_value = new_variable(name, value);/*more like new_value*/
			environ[exists] = malloc(sizeof(char) * (_strlen(old_value) + 1));
			if (environ[exists] == NULL)
			{
				unix_error("_setenv");
				free(old_value);/*won't be using it*/
				return (-1);
			}
			for (i = 0; old_value[i] != '\0'; i++)
				environ[exists][i] = old_value[i];
			environ[exists][i] = '\0';
			/*free(old_value);malloc'd in _getenv*/
		}
	}
	else
	{
		/*get to the end of array, extend it and add the new variable*/
		for (i = 0; environ[i] != NULL; i++)
			;
		environ[i++] =  new_variable(name, value);
		environ[i] = NULL;/*NULL terminate environ*/
	}
	return (0);
}

/**
 * _unsetenv - deletes an environment variable
 * @name: the environment variable's name
 * Return: 0 on success and -1 on error, seems to always pass?
 */
int _unsetenv(char *name)
{
	res res = {-1, -1}, *a_res = &res;
	int i, j;
	int var_index = get_name(environ, name, a_res);

	/*printf("var: %s\n", environ[var_index]);*/
	if (var_index != -1 && var_index)/*var_index not 0*/
	{
		/*delete it from the array - how?*/
		/*move all elements after it a pos forward*/
		i = var_index;
		j = i + 1;
		for (; environ[j] != NULL; i++, j++)
			environ[i] = environ[j];
		environ[i++] = NULL;/*terminate the environ array*/
		/*free(environ[i]);free the rest of environ? malloc'd at new_variable*/
	}
	return (0);
}


