#include "shell.h"

/**
 *error_puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void error_puts(char *string)
{
	int x = 0;

	if (!string)
		return;
	while (string[x] != '\0')
	{
		error_putchar(string[x]);
		x++;
	}
}

/**
 * error_putchar - Writes the character i to stderr.
 * @i: The character to print.
 * Return: On success, 1. On error, -1 is returned
 */

int error_putchar(char i)
{
	static int x;
	static char buf[W_BUFF_SIZE];

	if (i == FLUSH || x >= W_BUFF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (i != FLUSH)
		buf[x++] = i;
	return (1);
}

/**
 * put_fd - Writes the character i to the given file descriptor.
 * @i: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success, 1. On error, -1 is returned
 */

int put_fd(char i, int fd)
{
	static int x;
	static char buf[W_BUFF_SIZE];

	if (i == FLUSH || x >= W_BUFF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (i != FLUSH)
		buf[x++] = i;
	return (1);
}

/**
 * puts_fd - Prints an input string.
 * @string: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters put.
 */

int puts_fd(char *string, int fd)
{
	int x = 0;

	if (!string)
		return (0);
	while (*string)
	{
		x += put_fd(*string++, fd);
	}
	return (x);
}
