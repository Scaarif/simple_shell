#include "main.h"

/**
 * _write - print simple lines to stdout
 * @buf: buffer to hold string to write
 * @str: accompanying string, say name
 * @msg: customized message string
 * Return: no of characters written
 */
int _write(char *buf, char *str, char *msg)
{	int len = 0, i = 0;

	for (; (buf[len] = str[i]) != '\0'; i++, len++)
		;
	for (i = 0; (buf[len] = msg[i]) != '\0'; len++, i++)
		;
	i = write(1, buf, len);
	return (i);
}

/**
 * _strlen - strlen()
 * @s: string whose length to return
 * Return: length of string
 */
int _strlen(char s[])
{
	int i = 0;

	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * set_success - set success to true of false
 * @i: value to set success to
 * Return: Nothing
 */
void set_success(int i)
{
	(void)i;
	/*success = i;*/
}

/**
 * str_reverse - reverse a string
 * @s: the string to reverse
 * Return: Nothing
 */
void str_reverse(char s[])
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
 * _ltoa - convert long to base b string
 * @val: the long int
 * @s: string to hold the long
 * @base: base to which to convert the long
 * Return: Nothing
 */
void _ltoa(long val, char s[], int base)
{
	int c, i = 0;
	int neg = val < 0;

	if (neg)
		val *= -1;
	do {
		s[i++] = ((c = (val % base)) < 10) ? c + '0' : c + 'a';
	} while ((val /= base) > 0);

	if (neg)
		s[i++] = '-';
	s[i] = '\0'; /*terminate string*/
	str_reverse(s);
}
