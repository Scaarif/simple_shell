#include "main.h"

void add_to_setenvs(char **set_envs, char *var)
{
    int i = 0;

    if (set_envs[0] == NULL)
    {
        set_envs[0] = var;/*malloc'd*/
        set_envs[1] = NULL;
    }
    else
    {
        for (; set_envs[i] != NULL; i++)
            set_envs[i++] = var; 
        set_envs[i] = NULL;
    }
}
void remove_from_setenvs(char **set_envs, char *name)
{
    int i = 0, j;

    for (; set_envs[i] != NULL; i++)
    {
        if (_strcmp(set_envs[i], name) == 0)
        {
            j = i + 1;
            for (; set_envs[j] != NULL; i++, j++)
                _strcpy(set_envs[i], set_envs[j]);/*push forward the strings*/
            set_envs[j] = NULL;/*terminate*/
        }
    }
}

