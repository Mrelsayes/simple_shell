#include "shell.h"

/**
 * g_env - Returns the string array copy of our environ.
 * @inf: Structure containing potential arguments.
 *
 * Return: 0.
 */

char **g_env(get_info *inf)
{
	if (!inf->environ || inf->changed_environ)
	{
		inf->environ = liststr(inf->env);
		inf->changed_environ = 0;
	}

	return (inf->environ);
}

/**
 * unset_env - Removes an environment variable.
 * @inf: Structure containing potential arguments.
 * @v: The string representing the environment variable property.
 *
 * Return: 1 on deletion, 0 otherwise.
 */

int unset_env(get_info *inf, char *v)
{
	str_list *node = inf->env;
	size_t i = 0;
	char *x;

	if (!node || !v)
		return (0);

	while (node)
	{
		x = starts_w(node->str, v);
		if (x && *x == '=')
		{
			inf->changed_environ = rm_start_node(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->changed_environ);
}

/**
 * set_env - Initializes a new environment variable.
 * @inf: Structure containing potential arguments.
 * @v: The string representing the environment variable property.
 * @value: The string representing the environment variable value.
 *
 * Return: 0.
 */

int set_env(get_info *inf, char *v, char *value)
{
	char *buf = NULL;
	str_list *node;
	char *x;

	if (!v || !value)
		return (0);

	buf = malloc(str_len(v) + str_len(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, v);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = inf->env;
	while (node)
	{
		x = starts_w(node->str, v);
		if (x && *x == '=')
		{
			free(node->str);
			node->str = buf;
			inf->changed_environ = 1;
			return (0);
		}
		node = node->next;
	}
	node_end(&(inf->env), buf, 0);
	free(buf);
	inf->changed_environ = 1;
	return (0);
}
