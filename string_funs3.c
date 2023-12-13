#include "shell.h"

/**
 * strn_cpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The amount of characters to be copied.
 *
 * Return: Concatenated string.
 */

char *strn_cpy(char *dest, char *src, int n)
{
	int x, z;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		z = x;
		while (z < n)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (s);
}

/**
 * strn_cat - Concatenates two strings.
 * @dest: 1st string.
 * @src: 2nd string.
 * @n: The amount of bytes to be maximally used.
 *
 * Return: Concatenated string.
 */

char *strn_cat(char *dest, char *src, int n)
{
	int x, z;
	char *s = dest;

	x = 0;
	z = 0;
	while (dest[x] != '\0')
		x++;
	while (src[z] != '\0' && z < n)
	{
		dest[x] = src[z];
		x++;
		z++;
	}
	if (z < n)
		dest[x] = '\0';
	return (s);
}

/**
 * str_chr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: Pointer to the memory area s.
 */

char *str_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
