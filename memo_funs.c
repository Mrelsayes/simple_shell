#include "shell.h"

/**
 * mem_set - Fills memory with a constant byte.
 * @s: Pointer to the memory area.
 * @b: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */

char *mem_set(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * str_free - Frees string of strings.
 * @pp: String of strings.
 */

void str_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * re_alloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @size1: Byte size of the previous block.
 * @size2: Byte size of the new block.
 *
 * Return: Pointer to the old block.
 */

void *re_alloc(void *ptr, unsigned int size1, unsigned int size2)
{
	char *x;

	if (!ptr)
		return (malloc(size2));
	if (!size2)
		return (free(ptr), NULL);
	if (size2 == size1)
		return (ptr);

	x = malloc(size2);
	if (!x)
		return (NULL);

	size1 = size1 < size2 ? size1 : size2;
	while (size1--)
		x[size1] = ((char *)ptr)[size1];
	free(ptr);
	return (x);
}

#include "shell.h"

/**
 * buffer_free - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 || 0.
 */

int buffer_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
