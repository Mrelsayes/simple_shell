#include "shell.h"

/**
 * str_len - Returns the length of a string.
 * @str: The string whose length to check.
 *
 * Return: Integer length.
 */

int str_len(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * str_cmp - Performs lexicographic comparison of two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: - || + || 0
 */

int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_w - Checks if n starts with hstack.
 * @hstack: String to search.
 * @n: The substring to find.
 *
 * Return: Address of the next character || NULL.
 */

char *starts_w(const char *hstack, const char *n)
{
	while (*n)
		if (*n++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * str_cat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination.
 */

char *str_cat(char *dest, char *src)
{
	char *c = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (c);
}
