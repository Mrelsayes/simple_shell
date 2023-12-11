#include "shell.h"

/**
 * m_history - Displays the history list and one command per line.
 * @inf: Structure containing potential arguments
 * Return: 0.
 */

int m_history(get_info *inf)
{
	print_lists(inf->history);
	return (0);
}

/**
 * unset_alias - Assigns an alias to a string.
 * @inf: Parameter struct containing relevant information.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error.
 */

int unset_alias(get_info *inf, char *str)
{
	char *x, y;
	int z;

	x = str_chr(str, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	z = rm_start_node(&(inf->alias),
		get_start_node(inf->alias, node_start(inf->alias, str, -1)));
	*x = y;
	return (z);
}

/**
 * set_alias - Assigns an alias to a string.
 * @inf: Parameter struct.
 * @str: The string representing the alias.
 * Return: 0 on success, 1 on error.
 */

int set_alias(get_info *inf, char *str)
{
	char *x;

	x = str_chr(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(inf, str));

	unset_alias(inf, str);
	return (node_end(&(inf->alias), str, 0) == NULL);
}

/**
 * print_alias - Outputs the alias string.
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */

int print_alias(str_list *node)
{
	char *x = NULL, *y = NULL;

	if (node)
	{
		x = str_chr(node->str, '=');
		for (y = node->str; y <= x; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * m_alias - Mimics the alias built-in.
 * @inf: Structure containing potential arguments.
 * Return: 0.
 */

int m_alias(get_info *inf)
{
	int i = 0;
	char *x = NULL;
	str_list *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		x = str_chr(inf->argv[i], '=');
		if (x)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_start(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
