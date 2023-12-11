#include "shell.h"

/**
 * str_tow - Splits a string into words, ignoring repeated delimiters.
 * @string: The input string.
 * @delm: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */


char **str_tow(char *string, char *delm)
{
	int x, z, y, c, num = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (x = 0; string[x] != '\0'; x++)
		if (!is_delimeter(string[x], delm) && (is_delimeter(string[x + 1], delm)
		|| !string[x + 1]))
			num++;

	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, z = 0; z < num; z++)
	{
		while (is_delimeter(string[x], delm))
			x++;
		y = 0;
		while (!is_delimeter(string[x + y], delm) && string[x + y])
			y++;
		s[z] = malloc((y + 1) * sizeof(char));
		if (!s[z])
		{
			for (y = 0; y < z; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < y; c++)
			s[z][c] = string[x++];
		s[z][c] = 0;
	}
	s[z] = NULL;
	return (s);
}

/**
 * str_tow2 - Splits a string into words.
 * @string: The input string.
 * @delm: The delimiter.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **str_tow2(char *string, char delm)
{
	int x, z, y, c, num = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != delm && string[x + 1] == delm) ||
		    (string[x] != delm && !string[x + 1]) || string[x + 1] == delm)
			num++;
	if (num == 0)
		return (NULL);
	s = malloc((1 + num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, z = 0; z < num; z++)
	{
		while (string[x] == delm && string[x] != delm)
			x++;
		y = 0;
		while (string[x + y] != delm && string[x + y] && string[x + y] != delm)
			y++;
		s[z] = malloc((y + 1) * sizeof(char));
		if (!s[z])
		{
			for (y = 0; y < z; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (c = 0; c < y; c++)
			s[z][c] = string[x++];
		s[z][c] = 0;
	}
	s[z] = NULL;
	return (s);
}
