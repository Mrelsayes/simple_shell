#include "shell.h"

/**
 * str_cpy - Copies a string.
 * @dest: The destination.
 * @src: The source.
 * Return: Pointer to the destination.
 */

char *str_cpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * str_dup - Duplicates a string.
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string.
 */

char *str_dup(const char *str)
{
	int len = 0;
	char *c;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	c = malloc(sizeof(char) * (len + 1));
	if (!c)
		return (NULL);
	for (len++; len--;)
		c[len] = *--str;
	return (c);
}

/**
 * _puts - Prints an input string.
 * @str: The string to be printed.
 * Return: Nothing.
 */

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 * Return: On success, 1. On error, -1 is returned
 */

int _putchar(char c)
{
	static int x;
	static char buffer[W_BUFF_SIZE];

	if (c == FLUSH || x >= W_BUFF_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (c != FLUSH)
		buffer[x++] = c;
	return (1);
}
