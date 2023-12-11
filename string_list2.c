#include "shell.h"

/**
 * listlen - Determines the length of a linked list.
 * @ptr: Pointer to the first node.
 * Return: Size of the list.
 */

size_t listlen(const str_list *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * liststr - Returns an array of strings of the list->str.
 * @ptr: Pointer to the first node.
 * Return: Array of strings.
 */

char **liststr(str_list *ptr)
{
	str_list *node = ptr;
	size_t i = listlen(ptr), j;
	char **strs;
	char *str;

	if (!ptr || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_lists - Prints all elements of a str_list linked list.
 * @ptr: Pointer to the first node.
 * Return: Size of the list.
 */

size_t print_lists(const str_list *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		_puts(number_convertor(ptr->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * node_start - Returns a node whose string starts with the prefix.
 * @node: Pointer to the list ptr.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 * Return: Matched node or NULL.
 */

str_list *node_start(str_list *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_w(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_start_node - Gets the index of a node.
 * @ptr: Pointer to the list ptr.
 * @node: Pointer to the node.
 * Return: Index of the node or -1.
 */

ssize_t get_start_node(str_list *ptr, str_list *node)
{
	size_t i = 0;

	while (ptr)
	{
		if (ptr == node)
			return (i);
		ptr = ptr->next;
		i++;
	}
	return (-1);
}
