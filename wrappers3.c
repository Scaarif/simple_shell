#include "main.h"

/**
 * Sigprocmask - sigprocmask() wrapper
 * @how: what to do; block, unblock or reset blocked set
 * @set: the set to deal with (how)
 * @oldset: old set, blocked
 * Return: Nothing
 */
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
	if (sigprocmask(how, set, oldset) < 0)
		unix_error("Sigprocmask error");
}

/**
 * Sigfillset - sigfillset() wrapper, adds all sigs to set
 * @set: set to add signals to
 * Return: Nothing
 */
void Sigfillset(sigset_t *set)
{
	if (sigfillset(set) < 0)
		unix_error("Sigfillset error");
}

/**
 * Sigaddset - sigaddset() wrapper, adds a signal to a set
 * @set: the set to add signal to
 * @signum: signal to add to set
 * Return: Nothing
 */
void Sigaddset(sigset_t *set, int signum)
{
	if (sigaddset(set, signum) < 0)
		unix_error("Sigaddset error");
}

/**
 * Sigemptyset - sigemptyset() wrapper, initializes an empty set
 * @set: the set to initialize
 * Return: Nothing
 */
void Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) < 0)
		unix_error("Sigemptyset error");
}

/**
 * sio_error - safely write (print) an error msg
 * @s: the error msg
 * Return: Nothing
 */
void sio_error(char *s)
{
	sio_puts(s);
	_exit(0);/*safe termination*/
}
