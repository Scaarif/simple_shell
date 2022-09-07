#include "main.h"
/** SAFE I/O FUNCTIONS FOR SIGNAL HANDLERS **/
/*sio_error, sio_puts, Sio_puts & sio_putl*/

/**
 * sio_strlen - safe strlen?
 * @s: string whose length to return
 * Return: length of string
 */
static size_t sio_strlen(char s[])
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}
/**
 * sio_reverse - reverse a string
 * @s: the string to reverse
 * Return: Nothing
 */
static void sio_reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = _strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/**
 * sio_ltoa - convert long to base b string
 * @v: the long int
 * @s: string to hold the long
 * @b: base to which to convert the long
 * Return: Nothing
 */
static void sio_ltoa(long v, char s[], int b)
{
	int c, i = 0;
	int neg = v < 0;

	if (neg)
		v *= -1;
	do {
		s[i++] = ((c = (v % b)) < 10) ? c + '0' : c + 'a';
	} while ((v /= b) > 0);

	if (neg)
		s[i++] = '-';
	s[i] = '\0'; /*terminate string*/
	sio_reverse(s);
}

/**
 * sio_puts - safe print_string
 * @s: the tring to print
 * Return: no of characters written/printed
 */
ssize_t sio_puts(char s[])
{
	return (write(STDOUT_FILENO, s, sio_strlen(s)));
}

/**
 * sio_putl - safely prints a long
 * @v: the long int
 * Return: no of characters written
 */
ssize_t sio_putl(long v)
{
	char s[128];

	sio_ltoa(v, s, 10); /*based on K&R itoa (int to str)*/
	return (sio_puts(s));
}

/*sio_error was here*/

/** WRAPPER **/


