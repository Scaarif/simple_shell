#include "main.h"

/**
 * Execve - execve() wrapper
 * @filename: name of the executable file to run
 * @argv: cmd line args, NULL terminated array of strings
 * @envp: NULL terminated array of strings, environment variables
 * Return: (unsigned int) time left of 0 if elapsed
 */
void Execve(const char *filename, char *const argv[], char *const envp[])
{
	if (execve(filename, argv, envp) < 0)/*only returns if error*/
		unix_error("Execve error");
}

/**
 * Fgets - fgets() wrapper
 * @str: string read from stream
 * @size: no of chars to read - length of str
 * @stream: FILE to read from say stdin
 * Return: str
 */
char *Fgets(char *str, int size, FILE *stream)
{
	char *s = fgets(str, size, stream);

	if (s == NULL)
		unix_error("Logout");/*empty EOF exit shell*/
	return (s);
}

/**
 * Kill - kill() wrapper
 * @pid: process(s) to kill
 * @sig: the signal to send to process(pid)
 * Return: 0 if ok and -1 otherwise
 */
int Kill(pid_t pid, int sig)
{
	int res;

	res = kill(pid, sig);
	if (res < 0)
		unix_error("kill error");
	return (res);
}

/**
 * Sio_puts - sio_puts() wrapper
 * @s: str to print
 * Return: no of chars written
 */
ssize_t Sio_puts(char *s)
{
	ssize_t n = sio_puts(s);

	if (n < 0)
		sio_error("Sio_puts error");
	return (n);
}

/**
 * Signal - sigaction() wrapper
 * called the same way signal (for modifying signal action)
 * is called
 * @signum: the signal to catch
 * @handler: signal handler to install
 * Return: pointer to signal handler?
 */
handler_t *Signal(int signum, handler_t *handler)
{
	struct sigaction action, old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);/*block sigs of type being handled*/
	action.sa_flags = SA_RESTART; /*restart syscalls if possible*/

	if (sigaction(signum, &action, &old_action) < 0)
		unix_error("Signal error");
	return (old_action.sa_handler);
}










