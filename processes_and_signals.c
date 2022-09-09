#include "main.h"

/** HELPERS **/
/**
 * unix_error - handle system error
 * @msg: starting string
 * Return: 0 always
 */
int unix_error(const char *msg)
{
	perror(msg);
	return (0);
}

/**
 * sigint_handler - the handler installed
 * @sig: the SIGINT signal
 * Return: Nothing
 */
void sigint_handler(int sig)
{
	/*char buf[PATH_S];*/
	(void) sig;

	/*_write(buf, "", "");no need for this line!*/
}

/** WRAPPERS - call the base function and check for and handle errors **/
/**
 * Fork - fork() wrapper
 * Return: PID
 */
pid_t Fork(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		unix_error("Fork error");
	return (pid);
}

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

