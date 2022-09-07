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
	char buf[PATH_S];
	(void) sig;

	/*printf("Caught SIGINT!\n");*/
	_write(buf, "", "");/*no need for this line!*/
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
 * wakeup - sleep() wrapper
 * @secs: the period a process should sleep for
 * Return: (unsigned int) time left of 0 if elapsed
 */
unsigned int wakeup(unsigned int secs)
{
	unsigned int rem;

	rem = sleep(secs);
	/*printf("Slept for %u of %u secs.\n", secs - rem, secs);*/
	return (rem);
}

/**
 * Sleep - sleep() wrapper
 * @secs: the period a process should sleep for
 * Return: (unsigned int) time left of 0 if elapsed
 */
unsigned int Sleep(unsigned int secs)
{
	int rem;

	rem = sleep(secs);
	if (rem < 0)
		unix_error("Sleep error");
	return ((unsigned int)rem);
}

