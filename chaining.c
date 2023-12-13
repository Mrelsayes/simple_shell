#include "shell.h"

/**
 * ischain - Tests current character in the buffer is a chain delimiter.
 * @inf: The parameter struct.
 * @buffer: The character buffer.
 * @x: Address of the current position in buffer.
 *
 * Return: 1 if a chain delimiter or 0
 */

int ischain(get_info *inf, char *buffer, size_t *x)
{
	size_t z = *x;

	if (buffer[z] == '|' && buffer[z + 1] == '|')
	{
		buffer[z] = 0;
		z++;
		inf->type_cmd_buffer = OR_COMMAND;
	}
	else if (buffer[z] == '&' && buffer[z + 1] == '&')
	{
		buffer[z] = 0;
		z++;
		inf->type_cmd_buffer = AND_COMMAND;
	}
	else if (buffer[z] == ';')
	{
		buffer[z] = 0;
		inf->type_cmd_buffer = COMMAND_CHAIN;
	}
	else
		return (0);
	*x = z;
	return (1);
}

/**
 * chain_checker - Checks if we should continue chaining
 * @inf: The parameter struct.
 * @buffer: The character buffer.
 * @x: Address of the current position in buffer.
 * @i: Starting position in buffer.
 * @len: Length of buffer.
 *
 * Return: Void.
 */

void chain_checker(get_info *inf, char *buffer, size_t *x,
					size_t i, size_t len)
{
	size_t z = *x;

	if (inf->type_cmd_buffer == AND_COMMAND)
	{
		if (inf->status)
		{
			buffer[i] = 0;
			z = len;
		}
	}
	if (inf->type_cmd_buffer == OR_COMMAND)
	{
		if (!inf->status)
		{
			buffer[i] = 0;
			z = len;
		}
	}

	*x = z;
}

/**
 * alias_changer - Replaces aliases in the tokenized string.
 * @inf: The parameter struct.
 *
 * Return: 1 || 0
 */

int alias_changer(get_info *inf)
{
	int i;
	str_list *node;
	char *x;

	for (i = 0; i < 10; i++)
	{
		node = node_start(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		x = str_chr(node->str, '=');
		if (!x)
			return (0);
		x = str_dup(x + 1);
		if (!x)
			return (0);
		inf->argv[0] = x;
	}
	return (1);
}

/**
 * var_changer - Replaces variables in the tokenized string.
 * @inf: The parameter struct.
 *
 * Return: 1 || 0
 */

int var_changer(get_info *inf)
{
	int i = 0;
	str_list *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!str_cmp(inf->argv[i], "$?"))
		{
			string_changer(&(inf->argv[i]),
				str_dup(number_convertor(inf->status, 10, 0)));
			continue;
		}
		if (!str_cmp(inf->argv[i], "$$"))
		{
			string_changer(&(inf->argv[i]),
				str_dup(number_convertor(getpid(), 10, 0)));
			continue;
		}
		node = node_start(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			string_changer(&(inf->argv[i]),
				str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		string_changer(&inf->argv[i], str_dup(""));

	}
	return (0);
}

/**
 * string_changer - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 || 0
 */

int string_changer(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
