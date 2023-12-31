#include "shell.h"

/**
 * int_active - Returns true if the shell is in interactive mode.
 * @info: Structure address.
 *
 * Return: 1 || 0
 */

int int_active(get_info *info)
{
	return (isatty(STDIN_FILENO) && info->r_fd <= 2);
}

/**
 * is_delimeter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 || 0
 */

int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks for an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 || 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 || the converted number otherwise.
 */

int _atoi(char *str)
{
	int i, sig = 1, f = 0, output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && f != 2; i++)
	{
		if (str[i] == '-')
			sig *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			f = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (sig == -1)
		output = -result;
	else
		output = result;

	return (output);
}
