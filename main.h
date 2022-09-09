#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <dirent.h>
#include <string.h>
#include <signal.h>

#define	MAXLINE	 8192  /* Max text line length */
#define MAXJOBS    16
#define PATH_S 1024
#define BUFSIZE 1024
#define MAXARGS 128


extern char **environ;/*an external (global) variable - defined in Unix*/
/*int success;*/

typedef void handler_t(int);

/** STRUCTURES **/

/**
 * struct env_variable - response structure
 * for the get_name function, gets name of a variable
 * @var_index: index of the variable(in envp)
 * @val_index: string pointer to variable value
 */
typedef struct env_variable
{
	int var_index;
	int val_index;
} res;

/**
 * struct path_node - PATH directories linked list node
 * @dir: the directory(as path)
 * @next: the next dir in list
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
} d_t;

/* Process & signal handling functions */
int unix_error(const char *msg);
pid_t Fork(void);
void Execve(const char *filename, char *const argv[], char *const envp[]);
void sigint_handler(int sig);
handler_t *Signal(int signum, handler_t *handler);

/* Custom getline implementation */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* shell-functions */
void evaluate_command_line(char *cmdline, d_t *head);
char *handle_comments(char *buf);
char *format_command(char *cmd, char *command);
void variable_substitute(char **argv, int *status);
int builtin_command(char **argv, int *status);
char *check_for_delims(char *cmdline, char *delims, char *res);

/* Custom string functions - emulators of string.h functions  */
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strchr(char *s, char c);
int _strlen(char s[]);
char *_strcat(char *dest, char *src);

/* Environment handling functions */
char *_getenv(char **env, char *name, res *_res);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(char *name);
void add_to_setenvs(char **set_envs, char *var);
void remove_from_setenvs(char **set_envs, char *name);

/* PATH handling functions */
d_t *create_path_list(char *dir_str, d_t **head);
char *parse_path(d_t **head, char *file);
void free_path_list(d_t *head);
size_t print_pathlist(d_t *h);

/* General helper functions */
int _write(char *buf, char *str, char *msg);
void _ltoa(long val, char s[], int base);

#endif /*MAIN_H*/
