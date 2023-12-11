#include "shell.h"

/**
 * c_inf - Initializes the get_info struct.
 * @inf: Struct address.
 */

void c_inf(get_info *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - Initializes the get_info struct.
 * @inf: Struct address.
 * @av: Argument vector.
 */

void set_inf(get_info *inf, char **av)
{
	int x = 0;

	inf->file_name = av[0];
	if (inf->arg)
	{
		inf->argv = str_tow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = str_dup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (x = 0; inf->argv && inf->argv[x]; x++)
			;
		inf->argc = x;

		alias_changer(inf);
		var_changer(inf);
	}
}

/**
 * f_inf - Frees get_info struct fields.
 * @inf: Struct address.
 * @allfree: True if freeing allfree fields.
 */

void f_inf(get_info *inf, int allfree)
{
	str_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (allfree)
	{
		if (!inf->cmd_buffer)
			free(inf->arg);
		if (inf->env)
			freel(&(inf->env));
		if (inf->history)
			freel(&(inf->history));
		if (inf->alias)
			freel(&(inf->alias));
		str_free(inf->environ);
			inf->environ = NULL;
		buffer_free((void **)inf->cmd_buffer);
		if (inf->r_fd > 2)
			close(inf->r_fd);
		_putchar(FLUSH);
	}
}
