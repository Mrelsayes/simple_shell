#include "shell.h"

/**
 * m_env - Prints the current environment.
 * @inf: Structure containing potential arguments.
 *
 * Return: 0.
 */

int m_env(get_info *inf)
{
	print_string_list(inf->env);
	return (0);
}

/**
 * get_env - Gets the value of an environment variable.
 * @inf: Structure containing potential arguments
 * @name: Environment variable name.
 *
 * Return: The value.
 */

char *get_env(get_info *inf, const char *name)
{
	str_list *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_w(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * m_set_env - Initializes a new environment variable.
 * @inf: Structure containing potential arguments.
 *
 * Return: 0.
 */

int m_set_env(get_info *inf)
{
	if (inf->argc != 3)
	{
		error_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * m_unset_env - Removes an environment variable.
 * @inf: Structure containing potential arguments.
 *
 * Return: 0.
 */

int m_unset_env(get_info *inf)
{
	int x;

	if (inf->argc == 1)
	{
		error_puts("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= inf->argc; x++)
		unset_env(inf, inf->argv[x]);

	return (0);
}

/**
 * p_env_llist - Populates the environment linked list.
 * @inf: Structure containing potential arguments.
 *
 * Return: 0.
 */

int p_env_llist(get_info *inf)
{
	str_list *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		node_end(&node, environ[x], 0);
	inf->env = node;
	return (0);
}
